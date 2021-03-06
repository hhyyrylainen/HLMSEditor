/****************************************************************************
**
** Copyright (C) 2016 - 2017
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

// Include
#include <QMessageBox>
#include "brush_preset_dockwidget.h"
#include "mainwindow.h"
#include "magus_core.h"
#include "constants.h"

//****************************************************************************/
BrushPresetDockWidget::BrushPresetDockWidget(QString title, MainWindow* parent, Qt::WindowFlags flags) :
    QDockWidget (title, parent, flags),
    mParent(parent)
{
    mBrushWidget = new BrushWidget(BRUSH_PATH.c_str(), this);
    mPresetWidget = new PresetWidget(PRESET_PATH_QSTRING, this);
    mClipboardWidget = new ClipboardWidget(CLIPBOARD_PATH_QSTRING, this);
    mTabWidget = new QTabWidget(this);
    mTabWidget->addTab(mBrushWidget, QIcon(ICON_PAINT_ON), QString("Brushes"));
    mTabWidget->addTab(mPresetWidget, QIcon(ICON_HLMS), QString("Presets"));
    mTabWidget->addTab(mClipboardWidget, QIcon(ICON_PIN), QString("Clipboard"));
    connect(mBrushWidget, SIGNAL(brushDoubleClicked(QString,QString)), this, SLOT(handleBrushDoubleClicked(QString,QString)));
    connect(mPresetWidget, SIGNAL(presetCreateMaterial(QString,QString)), this, SLOT(handleCreateMaterial(QString,QString)));
    connect(mPresetWidget, SIGNAL(presetCreateMaterialAndApply(QString,QString)), this, SLOT(handleCreateMaterialAndApply(QString,QString)));
    setWidget(mTabWidget);
    mHelperString = "";
}

//****************************************************************************/
BrushPresetDockWidget::~BrushPresetDockWidget(void)
{
}

//****************************************************************************/
void BrushPresetDockWidget::handleBrushDoubleClicked(const QString& name, const QString& baseName)
{
    // Callback to parent
    mParent->setBrushInPaintLayer (name, baseName);
}

//****************************************************************************/
void BrushPresetDockWidget::handleCreateMaterial(const QString& name, const QString& baseName)
{
    // Create
    createMaterialFromPreset (name, baseName);
}

//****************************************************************************/
void BrushPresetDockWidget::handleCreateMaterialAndApply(const QString& name, const QString& baseName)
{
    // First delete the current material
    mParent->deleteCurrentMaterial();

    // Create...
    createMaterialFromPreset (name, baseName);

    // ...and apply
    mParent->applyCurrentMaterialToMesh();
}

//****************************************************************************/
void BrushPresetDockWidget::addPreset (const QString& path, const QString& thumbName)
{
    mPresetWidget->addPreset (path, thumbName);
}

//****************************************************************************/
void BrushPresetDockWidget::addToClipboard (const QString& filename)
{
    mClipboardWidget->addToClipboard(filename);
}

//****************************************************************************/
void BrushPresetDockWidget::useFromClipboard (const QString& fileName, const QString& baseName)
{
    // Delegate to the mainwindow, because it knows all the dockwidgets and can determine what to do
    mParent->useFromClipboard (fileName);
}

//****************************************************************************/
const QString& BrushPresetDockWidget::createMaterialFromPreset (const QString& name, const QString& baseName)
{
    mHelperString = "";
    QFileInfo info(name); // name is the name of the thumb image; it is only use to derive its path
    QDir sourceDir = info.absoluteDir();

    // First create the directory in the import path
    QSettings settings(FILE_SETTINGS, QSettings::IniFormat);
    QString importPath = settings.value(SETTINGS_IMPORT_PATH).toString();
    if (importPath.isEmpty())
        importPath = DEFAULT_IMPORT_PATH;
    QString presetImportPath = importPath + info.baseName();

    QDir targetDir(presetImportPath);
    if (!targetDir.exists())
    {
      targetDir.mkdir(".");
    }

    QString jsonFileName;
    Q_FOREACH(QFileInfo fileInfo, sourceDir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
    {
        if (!fileInfo.isDir())
        {
            QString fileName = fileInfo.absoluteFilePath();

            // Only check on images (but the thumb image is excluded) and hlms json files
            if (Magus::isTypeBasedOnExtension(fileName, Magus::MAGUS_SUPPORTED_IMAGE_FORMATS, Magus::MAGUS_SUPPORTED_IMAGE_FORMATS_LENGTH) && !fileName.contains(".json."))
            {
                // It is an image, so copy it
                QFile::copy(fileName, presetImportPath + "/" + fileInfo.fileName());
            }
            else if (fileInfo.suffix() == "json")
            {
                // It is a Hlms material name, so copy it
                jsonFileName = presetImportPath + "/" + fileInfo.fileName();
                QFile::copy(fileName, presetImportPath + "/" + fileInfo.fileName());
            }
        }
    }

    // Callback to parent
    if (!jsonFileName.isEmpty())
        mParent->loadMaterialAndCreateNodeStructure(jsonFileName);

    mHelperString = jsonFileName;
    return mHelperString;
}
