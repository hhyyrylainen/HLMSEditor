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
#include "constants.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "clipboard_widget.h"
#include "brush_preset_dockwidget.h"

//****************************************************************************/
ClipboardWidget::ClipboardWidget (const QString& clipboardDir, BrushPresetDockWidget* brushPresetDockWidget, QWidget* parent) :
    QWidget(parent),
    mBrushPresetDockWidget(brushPresetDockWidget)
{
    setWindowTitle(QString("Clipboard"));
    QHBoxLayout* mainLayout = new QHBoxLayout;
    QVBoxLayout* tableLayout = new QVBoxLayout;
    mClipboardDir = clipboardDir;

    QPixmap scriptPixmap(ICON_PIN);
    mGenericAssetWidget = new Magus::QtGenericAssetWidget(scriptPixmap, true, this);
    mGenericAssetWidget->setTextureSize(QSize(216, 48)); // Add 8 pixels to the width to compensate the frame width
    mGenericAssetWidget->setViewEnabled(false); // Don't display the context of the asset when doubleclicked
    mGenericAssetWidget->addContextMenuActionText(ACTION_USE_CURRENT_CLIP);
    mGenericAssetWidget->addContextMenuActionText(ACTION_DELETE_CURRENT_CLIP);
    loadClips (clipboardDir);
    connect(mGenericAssetWidget, SIGNAL(doubleClicked(QString,QString)), this, SLOT(handleDoubleClicked(QString,QString)));
    connect(mGenericAssetWidget, SIGNAL(contextMenuSelected(QAction*,QString,QString)), this, SLOT(handleContextMenuSelected(QAction*,QString,QString)));

    // Layout
    mainLayout->addWidget(mGenericAssetWidget);
    mainLayout->addLayout(tableLayout);
    setLayout(mainLayout);
}

//****************************************************************************/
ClipboardWidget::~ClipboardWidget (void)
{
}

//****************************************************************************/
void ClipboardWidget::loadClips (const QString& searchPath)
{
    // Get all texture files from all dirs/subdirs
    QDir dir(searchPath);
    dir.makeAbsolute();
    QString fileName;

    if (dir.exists())
    {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if (info.isDir())
            {
                loadClips(info.absoluteFilePath());
            }
            else
            {
                // A clip is a json file, so its extension is .json
                if (info.suffix() == "json")
                {
                    fileName = info.absoluteFilePath();
                    addToClipboard(fileName);
                }
            }
        }
    }
}

//****************************************************************************/
void ClipboardWidget::addToClipboard (const QString& filename)
{
    // Do not add duplicates
    if (mGenericAssetWidget->assetExists(filename))
        return;

    // Assume that only samplerblocks can be added to the clipbloard
    QFileInfo info(filename);
    QPixmap scriptPixmap(ICON_SAMPLER_CLIPBOARD);
    mGenericAssetWidget->addAsset(scriptPixmap, filename, info.baseName());
}

//****************************************************************************/
void ClipboardWidget::handleDoubleClicked (const QString& fileName, const QString& baseName)
{
    mBrushPresetDockWidget->useFromClipboard(fileName, baseName);
}

//****************************************************************************/
void ClipboardWidget::handleContextMenuSelected (QAction* action, const QString& name, const QString& baseName)
{
    if (action->text() == ACTION_USE_CURRENT_CLIP)
    {
        mBrushPresetDockWidget->useFromClipboard(name, baseName);
    }
    else if (action->text() == ACTION_DELETE_CURRENT_CLIP)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(0, "", "Are you sure you want to delete the clip?\n", QMessageBox::Ok|QMessageBox::Cancel);

        if (reply == QMessageBox::Ok)
        {
            mGenericAssetWidget->deleteAsset(name);
            QFile::remove(name);
        }
    }
}
