#include <node.h>
#include <vector>
#include "sort.h"
#include "sort.cpp"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Array;
// Преобразует JavaScript массив в C++ вектор, сортирует его слиянием,
// и конвертирует обратно в JavaScript массив.
void Method(const FunctionCallbackInfo<Value>& args) {
    // Инициализация изоляции из аргументов функции
    Isolate* isolate = args.GetIsolate();

    // Подготовка вектора для хранения чисел
    std::vector<double> array;

    // Приведение первого аргумента к типу Array
    Local<Array> jsArray = Local<Array>::Cast(args[0]);

    // Получение длины JavaScript массива
    int length = jsArray->Length();

    // Конвертация JavaScript массива в C++ вектор
    for (int i = 0; i < length; ++i) {
        Local<Value> jsValue = jsArray->Get(isolate->GetCurrentContext(), i).ToLocalChecked();
        double value = jsValue->NumberValue(isolate->GetCurrentContext()).FromJust();
        array.push_back(value);
    }

    // Сортировка вектора алгоритмом слияния
    mergeSort(array, 0, array.size() - 1);

    // Создание нового JavaScript массива для отсортированного результата
    Local<Array> resultArray = Array::New(isolate, array.size());

    // Заполнение JavaScript массива отсортированными значениями
    for (size_t i = 0; i < array.size(); ++i) {
        resultArray->Set(isolate->GetCurrentContext(), i, Number::New(isolate, array[i])).FromJust();
    }

    // Установка отсортированного массива в качестве возвращаемого значения
    args.GetReturnValue().Set(resultArray);
}

void Init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "sort", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init);
