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

#ifndef TEXTURE_THUMBS_H
#define TEXTURE_THUMBS_H

#include <QtWidgets>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "constants.h"
#include "tool_default_texturewidget.h"
#include "tool_resourcetree_widget.h"

QT_BEGIN_NAMESPACE
class QDockWidget;
QT_END_NAMESPACE

/****************************************************************************
This class represents a generic TextureThumbsDockWidget

IMPORTANT:
=========
This class is changed to facilitate the HLMS editor. Do not use it as a
generic Magus class.
***************************************************************************/
class TextureThumbsDockWidget : public QDockWidget
{
    Q_OBJECT

    public:
        TextureThumbsDockWidget(const QString& iconDir, const QString& title, QMainWindow* parent, Qt::WindowFlags flags = 0);
        ~TextureThumbsDockWidget(void);
        void createActions(void);
        void createMenus(void);
        void createToolBars(void);

        // Add texure resources
        void setResources(const QVector<Magus::QtResourceInfo*>& resources);

        // Add a texture file
        void addTextureFile (const QString& fileName);

        // Delete a texture file
        void deleteTextureFile (const QString& fileName);

        // Set baseNameThumb selected
        void setSelectThumb(const QString& fileName);

        // Apply filtering to the underlying widgets
        void filter(const QString& pattern);
        void filter(QStringList& resources);

        // Reset the filtering in the underlying widgets
        void resetFilter(void);

        // Return the full qualified filename of the currently selected thumb
        const QString& getCurrentFileName (void);

        // Return the pixmap of the selected thumb
        const QPixmap* getCurrentPixmap (void);

        // Clear all content in the underlying widgets
        void clearContent(void);

    signals:
        void tabChanged(int index);
        void assetDeleted(const QString& name, const QString& baseName);
        void assetSelected(const QString& name, const QString& baseName);
        void textureFileDropped(const QString& name, const QString& baseName);
        void assetDoubleClicked(const QString& name, const QString& baseName);

    private slots:
        void handleAssetDeleted(const QString& name, const QString& baseName);
        void handleAssetSelected(const QString& name, const QString& baseName);
        void handleTextureFileDropped(const QString& name, const QString& baseName);
        void handleAssetDoubleClicked(const QString& name, const QString& baseName);
        void handleContextMenuSelected (QAction* action, const QString& name, const QString& baseName);

    private:
        QMainWindow* mParent;
        QString mIconDir;
        Magus::QtDefaultTextureWidget* mTextureWidget;
};

#endif

