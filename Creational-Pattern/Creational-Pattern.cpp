#include <iostream>
#include <string>

using namespace std;
// Абстрактные продукты (семейство UI-элементов)
class Button {
public:
    virtual std::string render() = 0;
    virtual void interact() = 0;
};

class ScrollBar {
public:
    virtual std::string render() = 0;
    virtual void interact() = 0;
};

class CheckBox {
public:
    virtual std::string render() = 0;
    virtual void interact() = 0;
    
};
// Конкретные продукты для Windows
class WinButton : public Button {
public:
    std::string render() override { return "Windows Кнопка"; }
    void interact() override { std::cout << "Клик по Windows кнопке!\n"; }
};

class WinScrollBar : public ScrollBar {
public:
    std::string render() override { return "Windows Скроллбар"; }
    void interact() override { std::cout << "Прокрутка Windows скроллбара!\n"; }
};

class WinCheckBox : public CheckBox {
public:
    std::string render() override { return "Windows CheckBox"; }
    void interact() override { std::cout << "Отметка Windows CheckBox!\n"; }
};

// Конкретные продукты для macOS
class MacButton : public Button {
public:
    std::string render() override { return "macOS Кнопка"; }
    void interact() override { std::cout << "Клик по macOS кнопке!\n"; }
};

class MacScrollBar : public ScrollBar {
public:
    std::string render() override { return "macOS Скроллбар"; }
    void interact() override { std::cout << "Прокрутка macOS скроллбара!\n"; }
};

class MacCheckBox : public CheckBox {
public:
    std::string render() override { return "macOS CheckBox"; }
    void interact() override { std::cout << "Отметка macOS CheckBox!\n"; }
};

// Фабрика для линукса

class LinuxButton : public Button {
public:
    std::string render() override { return "Linux Кнопка"; }
    void interact() override { std::cout << "Клик по Linux кнопке!\n"; }
};

class LinuxScrollBar : public ScrollBar {
public:
    std::string render() override { return "Linux Скроллбар"; }
    void interact() override { std::cout << "Прокрутка Linux скроллбара!\n"; }
};

class LinuxCheckBox : public CheckBox {
public:
    std::string render() override { return "Linux CheckBox"; }
    void interact() override { std::cout << "Отметка Linux CheckBox!\n"; }
};

// Абстрактная фабрика
class UIFactory {
public:
    virtual Button* createButton() = 0;
    virtual ScrollBar* createScrollBar() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

// Конкретные фабрики
class WinFactory : public UIFactory {
public:
    Button* createButton() override { return new WinButton(); }
    ScrollBar* createScrollBar() override { return new WinScrollBar(); }
    CheckBox* createCheckBox() override { return new WinCheckBox(); }
};

class MacFactory : public UIFactory {
public:
    Button* createButton() override { return new MacButton(); }
    ScrollBar* createScrollBar() override { return new MacScrollBar(); }
    CheckBox* createCheckBox() override { return new MacCheckBox(); }
};

class LinuxFactory : public UIFactory {
public:
    Button* createButton() override { return new LinuxButton(); }
    ScrollBar* createScrollBar() override { return new LinuxScrollBar(); }
    CheckBox* createCheckBox() override { return new LinuxCheckBox(); }
};

int main() {
    // Выбираем фабрику по платформе
    setlocale(LC_ALL, "ru");
    int x;
    cout << "Выберите платформу: \n1 - Win\n2 - Mac\n3 - Lin\nВаш выбор: " << endl;
    cin >> x;
    if (x == 1)
    {
        UIFactory* factory = new WinFactory();
        Button* btn = factory->createButton();
        ScrollBar* sb = factory->createScrollBar();
        CheckBox* cb = factory->createCheckBox();
        std::cout << btn->render() << " и " << sb->render() << " и " << cb->render() << std::endl;
        btn->interact();
        sb->interact();
        cb->interact();
        delete btn; delete sb; delete factory;
    }
    else if (x == 2)
    {
        UIFactory* factory = new MacFactory();
        Button* btn = factory->createButton();
        ScrollBar* sb = factory->createScrollBar();
        CheckBox* cb = factory->createCheckBox();
        std::cout << btn->render() << " и " << sb->render() << " и " << cb->render() << std::endl;
        btn->interact();
        sb->interact();
        cb->interact();
        delete btn; delete sb; delete factory;
    }
    else if (x == 3)
    {
        UIFactory* factory = new LinuxFactory();
        Button* btn = factory->createButton();
        ScrollBar* sb = factory->createScrollBar();
        CheckBox* cb = factory->createCheckBox();
        std::cout << btn->render() << " и " << sb->render() << " и " << cb->render() << std::endl;
        btn->interact();
        sb->interact();
        cb->interact();
        delete btn; delete sb; delete factory;
    }
    else {
        cout << "Вы ввели неккоректное число" << endl;
    }

    return 0;
}
