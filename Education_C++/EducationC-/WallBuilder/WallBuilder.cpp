#include <iostream>
#include <vector>
using namespace std;

class IWallBuilder {
public:
    virtual void build(int height, int width, char symbol) = 0;
};

class WallBuilder : public IWallBuilder {
public:
    void build(int height, int width, char symbol) override {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << symbol;
            }
            cout << endl;
        }
    }
};

class WallBuilderDecorator : public IWallBuilder {
private:
    IWallBuilder* builder;
public:
    WallBuilderDecorator(IWallBuilder* b) : builder(b) {}
    void build(int height, int width, char symbol) override {
        if (height < 1) height = 1;
        if (width < 1) width = 1;
        if (height > 50) height = 50;
        if (width > 50) width = 50;
        builder->build(height, width, symbol);
        cout << "Я исправил ошибки" << endl;
    }
};
int main() {
    setlocale(LC_ALL, "rus");
    vector<IWallBuilder*> builders;

    builders.push_back(new WallBuilder());
    builders.back()->build(3, 5, '#');
    cout << endl;

    builders.back()->build(1, 15, '|');
    cout << endl;

    builders.push_back(new WallBuilderDecorator(new WallBuilder()));

    builders.back()->build(3, 5, '*');
    cout << endl;

    builders.back()->build(1, 15, '^');
    cout << endl;

    return 0;
}
