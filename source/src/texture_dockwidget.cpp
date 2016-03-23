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

// Include
#include "mainwindow.h"
#include "texture_dockwidget.h"

//****************************************************************************/
TextureDockWidget::TextureDockWidget(QString title, MainWindow* parent, Qt::WindowFlags flags) :
	QDockWidget (title, parent, flags), 
    mParent(parent)
{
    mTextureMain = new TextureMain("../common/icons/"); // TODO: Use const string
    setWidget(mTextureMain);

    // Perform standard functions
    createActions();
    createMenus();
    createToolBars();
}

//****************************************************************************/
TextureDockWidget::~TextureDockWidget(void)
{
}

//****************************************************************************/
void TextureDockWidget::createActions(void)
{
    connect(mTextureMain, SIGNAL(customContextMenuItemSelected(QString)), this, SLOT(handleCustomContextMenuItemSelected(QString)));
    connect(mTextureMain, SIGNAL(textureDoubleClicked(int,int,int,QString,QString)), this, SLOT(handleTextureDoubleClicked(int,int,int,QString,QString)));
    connect(mTextureMain, SIGNAL(textureMutationOccured()), this, SLOT(handleTextureMutationOccured()));
}

//****************************************************************************/
void TextureDockWidget::createMenus(void)
{
}

//****************************************************************************/
void TextureDockWidget::createToolBars(void)
{
}

//****************************************************************************/
QVector<Magus::QtResourceInfo*>& TextureDockWidget::getResources (void)
{
    // Delegate to mTextureMain
    return mTextureMain->getResources();
}

//****************************************************************************/
void TextureDockWidget::setResources (const QVector<Magus::QtResourceInfo*>& resources)
{
    mTextureMain->setResources(resources);
}

//****************************************************************************/
void TextureDockWidget::addTextureFile (const QString& fileName)
{
    mTextureMain->addTextureFile(fileName);
}

//****************************************************************************/
void TextureDockWidget::addTextureFile (const QString& fileName, const QString& group)
{
    mTextureMain->addTextureFile(fileName, group);
}

//****************************************************************************/
const QString& TextureDockWidget::getCurrentFileName (void)
{
    return mTextureMain->getCurrentFileName();
}

//****************************************************************************/
void TextureDockWidget::handleTextureDoubleClicked(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName)
{
    emit textureDoubleClicked(name, baseName);
}

//****************************************************************************/
void TextureDockWidget::handleCustomContextMenuItemSelected(const QString& menuItemText)
{
    emit customContextMenuItemSelected(menuItemText);
}

//****************************************************************************/
void TextureDockWidget::handleTextureMutationOccured(void)
{
    emit textureMutationOccured();
}
