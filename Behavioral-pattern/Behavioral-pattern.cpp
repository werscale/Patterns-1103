#include <iostream>
#include <string>

using namespace std;
// Контекст: Автомат
class VendingMachine;

// Абстрактное состояние
class State {
public:
    virtual void insertCoin(VendingMachine* vm) = 0;
    virtual void dispense(VendingMachine* vm) = 0;
    virtual void ejectCoin(VendingMachine* vm) = 0;
};

// Конкретные состояния
class NoCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override;
    void dispense(VendingMachine* vm) override { std::cout << "Вставьте монету сначала!" << std::endl; }
    void ejectCoin(VendingMachine* vm) override { std::cout << "Вставьте монету сначала!" << std::endl; };
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* vm) override { std::cout << "Монета уже вставлена!" << std::endl; }
    void dispense(VendingMachine* vm) override;
    void ejectCoin(VendingMachine* vm) override;
};

class SoldOutState : public State {
public:
    void insertCoin(VendingMachine* vm) override;
    void dispense(VendingMachine* vm) override { std::cout << "Напитки закончились!" << std::endl; };
    void ejectCoin(VendingMachine* vm) override { std::cout << "Напитки закончились!" << std::endl; };
};

class WinnerState : public State {
public:
    void insertCoin(VendingMachine* vm) override { std::cout << "Монетка уже вставлена!" << std::endl; };
    void dispense(VendingMachine* vm) override;
    void ejectCoin(VendingMachine* vm) override;
};

class VendingMachine {
private:
    State* currentState;
public:
    VendingMachine() {
        currentState = new NoCoinState();
    }
    ~VendingMachine() { delete currentState; }
    void setState(State* s) { delete currentState; currentState = s; }
    void insertCoin() { currentState->insertCoin(this); }
    void ejectCoin() { currentState->ejectCoin(this); }
    void dispense() { currentState->dispense(this); }
};

void NoCoinState::insertCoin(VendingMachine* vm) {
    cout << "Монета вставлена." << std::endl;
    vm->setState(new WinnerState()); // лотерея вместо обычного
}

void HasCoinState::dispense(VendingMachine* vm) {
    cout << "Напиток выдан!" << std::endl;
    vm->setState(new SoldOutState());
}

void SoldOutState::insertCoin(VendingMachine* vm) {
    cout << "Напиток выдан!" << std::endl;
    vm->setState(new SoldOutState());
}

void HasCoinState::ejectCoin(VendingMachine* vm) {
    cout << "Монетка вернулась!" << std::endl;
    vm->setState(new NoCoinState());
}

void WinnerState::dispense(VendingMachine* vm) {
    cout << "Напиток выдан!" << std::endl;
    if (rand() % 2 == 1)
    {
        cout << "Вы выйграли подолнительный напиток!" << std::endl;
    }
    vm->setState(new NoCoinState());
}

void WinnerState::ejectCoin(VendingMachine* vm) {
    if (rand() % 2 == 0)
    {
        cout << "Монетка вернулась!" << std::endl;
        vm->setState(new NoCoinState());
    }
    else
    {
        cout << "Монетка вернулась, но автомат всё ещё может выдать напиток!" << std::endl;
    }
}

int main() {
    setlocale(0, "");

    VendingMachine vm;
    vm.dispense();  // Вывод: Вставьте монету сначала!
    vm.insertCoin();  // Вывод: Монета вставлена.
    //vm.dispense();  // Вывод: Напиток выдан!
    vm.ejectCoin();
    vm.dispense(); // Нет напитков!
    return 0;
}