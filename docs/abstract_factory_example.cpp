#include <iostream>
#include <vector>

// ����������� ������� ������ ��������
class Window {
  public:
    virtual void info() = 0;
    virtual ~Window() {}
};

class ScrollBar {
  public:
    virtual void info() = 0;
    virtual ~ScrollBar() {}
};

class Button {
  public:
    virtual void info() = 0;
    virtual ~Button() {}
};


// ������ ���� ����� ��������, ����������� �� ��������� Motif
class MotifWindow: public Window {
  public:
    void info() {
      std::cout << "MotifWindow" << std::endl;
    }
};

class MotifScrollBar: public ScrollBar {
  public:
    void info() {
      std::cout << "MotifScrollBar" << std::endl;
    }
};

class MotifButton: public Button {
  public:
    void info() {
      std::cout << "MotifButton" << std::endl;
    }
};


// ������ ���� ����� ��������, ����������� �� ��������� PresentationManager
class PMWindow: public Window {
  public:
    void info() {
      std::cout << "PMWindow" << std::endl;
    }
};

class PMScrollBar: public ScrollBar {
  public:
    void info() {
      std::cout << "PMScrollBar" << std::endl;
    }
};

class PMButton: public Button {
  public:
    void info() {
      std::cout << "PMButton" << std::endl;
    }
};


// ����������� ������� ��� ������������ ��������
class WidgetFactory {
  public:
    virtual Window* createWindow() = 0;
    virtual ScrollBar* createScrollBar() = 0;
    virtual Button* createButton() = 0;
    virtual ~WidgetFactory() {}
};


// ������� ��� �������� ��������, ����������� �� ��������� Motif
class MotifWidgetFactory: public WidgetFactory {
  public:
    Window* createWindow() {
      return new MotifWindow;
    }
    ScrollBar* createScrollBar() {
      return new MotifScrollBar;
    }
    Button* createButton() {
      return new MotifButton;
    }
};


// ������� ��� �������� ��������, ����������� �� ��������� PresentationManager
class PMWidgetFactory: public WidgetFactory {
  public:
    Window* createWindow() {
      return new PMWindow;
    }
    ScrollBar* createScrollBar() {
      return new PMScrollBar;
    }
    Button* createButton() {
      return new PMButton;
    }
};


// �����, ���������� ��� ������� ���� ��� ����� ��������� ����������
class Interface {
  public:
   ~Interface() {
      delete window;
      delete scrollbar;
      delete button;
    }
    void info() {
      window->info();
      scrollbar->info();
      button->info();
    }
    Window* window;
    ScrollBar* scrollbar;
    Button* button;
};


// ����� ��������� ��������� � ������������ � ��� ��� ���� ���������� ����������
class App {
  public:
    Interface* createInterface( WidgetFactory& factory ) {
      Interface* p = new Interface;
      p->window = factory.createWindow();
      p->scrollbar = factory.createScrollBar();
      p->button = factory.createButton();
      return p;
    }
};


int main() {
    App app;

    MotifWidgetFactory motif_factory;
    Interface* motif = app.createInterface(motif_factory);
    std::cout << "Motif Interface:" << std::endl;
    motif->info();
    // ...

    // ���

    PMWidgetFactory pm_factory;
    Interface* pm = app.createInterface(pm_factory);
    std::cout << "\nPM Interface:" << std::endl;
    pm->info();
    // ...
}
