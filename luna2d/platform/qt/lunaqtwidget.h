//-----------------------------------------------------------------------------
// luna2d engine
// Copyright 2014-2017 Stepan Prokofjev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#pragma once

#include "lunaengine.h"
#include "lunaqtlog.h"
#include <QOpenGlWidget>
#include <QOpenGLPaintDevice>

namespace luna2d{

const float MAX_FPS = 60.0f;

class LUNAQtWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	explicit LUNAQtWidget(QWidget* parent = 0);
	virtual ~LUNAQtWidget();

private:
	QOpenGLPaintDevice* paintDevice = nullptr;
	QColor placeholderColor = Qt::white;
	QImage placeholderImage;
	bool mouseDown = false;
	bool autoPause = true;

private:
	float TranslateMouseX(int x);
	float TranslateMouseY(int y);

protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual bool eventFilter(QObject* target, QEvent* event);

signals:
	void engineInitialized(); // Emits when engine was initialized
	void glSurfaceInitialized(); // Emits after GL surface complete initialized
	void gameLoopIteration(); // Emits every game loop iteration

	// Emits when occurs any log message
	void logInfo(const QString& message);
	void logWarning(const QString& message);
	void logError(const QString& message);

	// Emits when game send analytics event
	void analyticsDataSent(const QString& event, const QHash<QString,QString>& data);

public:
	bool IsEngineInitialized();
	void InitializeEngine(const QString& gamePath, int width, int height);
	void InitializeEngine(const QString& gamePath);
	void RunGame();
	void DeinitializeEngine();
	void PauseEngine();
	void ResumeEngine();
	bool IsEnginePaused();
	LUNAEngine* GetEngine();
	void SetPlaceholderColor(const QColor& color);
	void SetPlaceholderImage(const QImage& image);
	int GetFps();
	QString GetGameName();
};

}
