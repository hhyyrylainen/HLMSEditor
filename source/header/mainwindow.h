/****************************************************************************
**
** Copyright (C) 2016
**
** This file is generated by the Magus toolkit
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QList>
#include "OgreDataStream.h"
#include "OgreMesh2.h"
#include "Ogre.h"
#include "renderwindow_dockwidget.h"
#include "properties_dockwidget.h"
#include "texture_dockwidget.h"
#include "nodeeditor_dockwidget.h"
#include "paint_dockwidget.h"
#include "brush_dockwidget.h"
#include "paintlayer_dockwidget.h"
#include "central_dockwidget.h"
#include "material_browser_dialog.h"
#include "ogre3_renderman.h"
#include "hlms_editor_plugin.h"
#include "recent_file_action.h"
#include "hlms_utils_manager.h"
#include "paintlayer_manager.h"
#include "constants.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

/****************************************************************************
 MainWindow is the main container window
 ***************************************************************************/
class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow(void);
		~MainWindow(void);
        bool eventFilter(QObject* object, QEvent* event);
		void update(void);
		bool mIsClosing;
        PaintLayerManager mPaintLayerManager;

        Magus::OgreManager* getOgreManager(void) const {return mOgreManager;}
        RenderwindowDockWidget* mRenderwindowDockWidget; // Make is public for easy access
        PropertiesDockWidget* mPropertiesDockWidget; // Make is public for easy access
        TextureDockWidget* mTextureDockWidget; // Make is public for easy access
        PaintDockWidget* mPaintDockWidget; // Make is public for easy access
        BrushDockWidget* mBrushDockWidget; // Make is public for easy access
        PaintLayerDockWidget* mPaintLayerDockWidget; // Make is public for easy access
        void initCurrentDatablockFileName(void); // Set the name of the current json file to ""
        void getListOfResources(void); // Function to test which resources are loaded
        EditorHlmsTypes getCurrentDatablockType(void); // Returns the current hlms type
        void loadTextureBrowserCfg(void);
        void setCurrentDatablockIdAndFullName(const Ogre::IdString& datablockId, const Ogre::String& fullName);
        QVector<int> getSubItemIndicesWithDatablockAndReplaceWithDefault(const Ogre::IdString& datablockId); // Get list of indeces, which have datablock 'datablockId'
        void replaceCurrentDatablock(QVector<int> indices, Ogre::IdString datablockId); // Set the datablocks in the subItems, identified by 'indices'
        const Ogre::String& getCurrentDatablockFullName (void) {return mCurrentDatablockFullName;}
        const Ogre::IdString& getCurrentDatablockId (void) {return mCurrentDatablockId;}
        void destroyDatablock(const Ogre::IdString& datablockId);
        void notifyHlmsChanged (QtProperty* property); // To be called if the properties of a datablock are changed (which result in rebuilding the material)
        HlmsUtilsManager* getHlmsUtilsManager (void) {return mHlmsUtilsManager;}
        const Ogre::String& getTextureFileNameOfPbs(const Ogre::IdString& datablockId, Ogre::PbsTextureTypes textureType); // Returns the filename of a pbs texture type
        PaintLayers* getPaintLayers(void); // Returns pointer to the paintlayers, managed by the PainLayerManager
        void setBrushInPaintLayer(const QString& name, const QString& baseName); // If a brush is selected, set the new brush in the PaintLayer
        void loadTextureGeneration (Ogre::PbsTextureTypes textureType, Ogre::ushort sequence); // Load a texture, based on the type and sequence (texture is blit to the GPU)
        void notifyNodeDeleted(unsigned int nodeType); // Is called by the node editor if a node is deleted
        void addResourceLocationFile (const QString& fileName);
        void addResourceLocationPath (const QString& path);

    protected:
        void saveResources(const QString& fileName, const QVector<Magus::QtResourceInfo*>& resources); // Save the content of a resource vector
        QMessageBox::StandardButton fileDoesNotExistsWarning(const QString& fileName);
        void newProjectName(void);
        void appendRecentHlms(const QString fileName); // Used for recent Hlms files in menu
        void appendRecentProject(const QString fileName); // Used for recent Project files in menu
        bool isMeshV1(const QString meshFileName);
        bool isMeshV2(const QString meshFileName);
        unsigned int getMeshVersion(const QString meshFileName);
        Ogre::MeshPtr convertMeshV1ToV2(const QString fileNameMeshV1);
        void saveV2Mesh(Ogre::MeshPtr v2MeshPtr, QString meshFileName);
        void detachMaterialsFromItem (void);
        void restoreMaterialsOfItem (void);
        void createSpecialDatablocks (void);
        void destroySpecialDatablocks(void);
        void setDatablocksFromMaterialBrowserInItem(void);
        const Ogre::String& getJsonFileNameFromMaterialBrowser(const Ogre::String& fullName);
        void createActions(void);
        void createMenus(void);
        void createToolBars(void);
        void createStatusBar(void);
        void createDockWindows(void);
        void closeEvent(QCloseEvent* event);
        void loadDatablockAndSet(const QString jsonFileName);
        void loadMesh(const QString meshFileName);
        void loadProject(const QString& fileName);
         // Saves the current datablock; if validatePaintLayers is true, the validation whether there are paintlayers must still be done
        void saveDatablock(bool validatePaintLayers);
        bool continueEvenIfThereArePaintLayers(void); // Validate whether there are paintlayers (before saving the datablock)

        void loadMaterialBrowserCfg(void);
        void saveMaterialBrowserCfg(void);
        void loadRecentHlmsFilesCfg(void);
        void saveRecentHlmsFilesCfg(void);
        void loadRecentProjectFilesCfg(void);
        void saveRecentProjectFilesCfg(void);
        Ogre::DataStreamPtr openFile(Ogre::String source);
        void clearHlmsNamesAndRemovePaintLayers(void);
        void deleteTempPathRecursive(void);

	private slots:
        void doNewProjectAction(void);
        void doNewHlmsPbsAction(void);
        void doNewHlmsUnlitAction(void);
        void doOpenProjectMenuAction(void);
        void doOpenDatablockMenuAction(void);
        void doOpenMeshMenuAction(void);
        void doSaveProjectMenuAction(void);
        void doSaveDatablockMenuAction(void);
        void doSaveAsProjectMenuAction(void);
        void doSaveAsDatablockMenuAction(void);
        void doSaveAsMeshMenuAction(void);
        void doMaterialSetMenuAction(void);
        void doMaterialBrowserOpenMenuAction(void);
        void doMaterialBrowserAddMenuAction(void);
        void doQuitMenuAction(void);
        void doTextureBrowserImportMenuAction(void);
        void doTextureBrowserAddImageMenuAction(void);
        void doNewPaintingLayerMenuAction(void);
        void doEditPaintingLayerMenuAction(void);
        void doSelectedPaintingLayersMenuAction(void);
        void doConfigureMenuAction(void);
        void doResetWindowLayoutMenuAction(void);
        void handleTextureDoubleClicked(const QString& fileName, const QString& baseName);
        void handleCustomContextMenuItemSelected(const QString& menuItemText);
        void handleTextureMutationOccured(void);
        void saveTextureBrowserCfg(void);
        void doImport(Ogre::HlmsEditorPlugin* plugin);
        void doExport(Ogre::HlmsEditorPlugin* plugin);
        void constructHlmsEditorPluginData(Ogre::HlmsEditorPluginData* data);
        void doRecentHlmsFileAction(const QString& fileName);
        void doRecentProjectFileAction(const QString& fileName);
        void doMaterialBrowserAccepted(const QString& fileName);
        void doMaterialBrowserRejected(void);
        void doMaterialBrowserClosed(void);

	private:
        bool mFirst;
        QString mTempString;
        Ogre::String mTempOgreString;
        MaterialBrowserDialog* mMaterialBrowser;
        QMenu* mFileMenu;
        QMenu* mMaterialMenu;
        QMenu* mTextureMenu;
        QMenu* mWindowMenu;
        QMenu* mRecentHlmsFilesMenu;
        QMenu* mRecentProjectFilesMenu;
        QAction* mNewProjectAction;
        QAction* mNewHlmsPbsAction;
        QAction* mNewHlmsUnlitAction;
        QAction* mOpenProjectMenuAction;
        QAction* mOpenDatablockMenuAction;
        QAction* mOpenMeshMenuAction;
        QAction* mSaveProjectMenuAction;
        QAction* mSaveDatablockMenuAction;
        QAction* mSaveAsProjectMenuAction;
        QAction* mSaveAsDatablockMenuAction;
        QAction* mSaveAsMeshMenuAction;
        QAction* mMaterialSetMenuAction;
        QAction* mMaterialBrowserOpenMenuAction;
        QAction* mMaterialBrowserAddMenuAction;
        QAction* mTextureBrowserImportMenuAction;
        QAction* mNewPaintingLayerAction;
        QAction* mEditPaintingLayerAction;
        QAction* mDeleteSelectedPaintingLayersAction;
        QAction* mConfigureMenuAction;
        QAction* mTextureBrowserAddImageMenuAction;
        QAction* mRecentHlmsFilesMenuAction;
        QAction* mRecentProjectFilesMenuAction;
        QAction* mQuitMenuAction;
        QAction* mResetWindowLayoutMenuAction;
        NodeEditorDockWidget* mNodeEditorDockWidget;
        CentralDockWidget* mCentralDockWidget;
        Magus::OgreManager* mOgreManager;
        QString mProjectName;
        QString mProjectPath;
        QString mMaterialFileName;
        QString mTextureFileName;
        QString mHlmsName; // Used to determine whether a hlms was already saved
        Ogre::IdString mCurrentDatablockId; // The datablock id
        Ogre::String mCurrentDatablockFullName; // The datablock full name
        bool mSaveTextureBrowserTimerActive;
        struct RecentFileStruct
        {
            RecentFileAction* action;
            QString fileName;
        };
        QList<RecentFileStruct> mRecentHlmsFiles; // Used for recent Hlms files in menu
        QList<RecentFileStruct> mRecentProjectFiles; // Used for recent Project files in menu
        QPoint mMaterialBrowserPosition;
        QSize mMaterialBrowserSize;
        HlmsUtilsManager* mHlmsUtilsManager;
        Ogre::String mHelperName;
        QVector<int> helperIndices;
};

#endif

