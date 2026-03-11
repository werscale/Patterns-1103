#include <iostream>
#include <string>

using namespace std;
// Новый интерфейс принтера (USB)
class USBPrinter {
public:
    virtual std::string printUSB(const std::string& data, int quality) = 0;
    virtual ~USBPrinter() {}
};

// Новый интерфейс сканера (USB)
class USBScanner {
public:
    virtual std::string scanUSB(int quality) = 0;
    virtual ~USBScanner() {}
};


// Старый принтер (LPT)
class OldLPTPrinter {
public:
    std::string printLPT(const std::string& data) {
        return "Старый принтер печатает по LPT: " + data;
    }
};

// Старый сканер (LPT)
class OldLPTScanner {
public:
    std::string scanLPT() {
        return "Сканирование через старый LPT-сканер";
    }
};


// Адаптер принтера
class LPTToUSBPrinterAdapter : public USBPrinter {
private:
    OldLPTPrinter* oldPrinter;

public:
    LPTToUSBPrinterAdapter(OldLPTPrinter* p) : oldPrinter(p) {}

    std::string printUSB(const std::string& data, int quality) override {
        std::string adapted = data + " | качество: " + std::to_string(quality);
        return oldPrinter->printLPT(adapted + " (адаптировано для USB)");
    }
};

// Адаптер сканера
class LPTToUSBScannerAdapter : public USBScanner {
private:
    OldLPTScanner* oldScanner;

public:
    LPTToUSBScannerAdapter(OldLPTScanner* s) : oldScanner(s) {}

    string scanUSB(int quality) override {
        string result = oldScanner->scanLPT();
        return result + " | качество: " + std::to_string(quality) + " USB адаптер";
    }
};



class ClassPrinterAdapter : public USBPrinter, public OldLPTPrinter {
public:
    string printUSB(const std::string& data, int quality) override {
        string adapted = data + " | качество: " + std::to_string(quality);
        return printLPT(adapted + " Класс адаптер");
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    OldLPTPrinter oldPrinter;
    OldLPTScanner oldScanner;

    USBPrinter* printAdapter = new LPTToUSBPrinterAdapter(&oldPrinter);
    USBScanner* scannAdapter = new LPTToUSBScannerAdapter(&oldScanner);

    cout << printAdapter->printUSB("Документ", 90) << std::endl;
    cout << scannAdapter->scanUSB(75) << std::endl;

    USBPrinter* classAdapter = new ClassPrinterAdapter();
    cout << classAdapter->printUSB("Фото", 100) << std::endl;

    delete printAdapter;
    delete scannAdapter;
    delete classAdapter;


    return 0;
}
