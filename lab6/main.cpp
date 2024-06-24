#include <iostream>
#include "libusb-1.0/libusb.h"
#include <stdio.h>
#include <clocale>
#include <vector>
#include <map>
using namespace std;

map<int, string> usbClasses = {
        {1, "аудио"},
        {2, "коммуникационное устройство"},
        {3, "устройство пользовательского интерфейса"},
        {5, "физическое устройство"},
        {6, "изображение"},
        {7, "принтер"},
        {8, "устройство хранения данных"},
        {9, "hub"},
        {10, "CDC-Data"},
        {11, "Smart card"},
        {13, "Content Security"},
        {14, "видеоустройство"},
        {15, "персональное медицинское устройство"},
        {16, "аудио- и видеоустройства"},
        {17, "Класс устройства Billboard"},
        {18, "USB Type-C Bridge Class"},
        {220, "диагностическое устройство"},
        {224, "беспроводный контроллер"},
        {239, "различные устройства"},
        {254, "специфическое устройство"}
};

void printdev(libusb_device *dev){
    libusb_device_descriptor desc; // дескриптор устройства
    libusb_config_descriptor *config; // дескриптор конфигурации объекта
    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0){
        fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n", r);
        return;
    }
    libusb_device_handle* handle = nullptr;
    unsigned char str[256] = "";
    int ret = libusb_open(dev, &handle);
    if (LIBUSB_SUCCESS == ret) {
        ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, str, 256);
        if (ret > 0) {
            cout << "Название: " << str <<endl;
        }
        ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, str, 256);
        if (ret > 0) {
            cout << "Серийный номер: " << str <<endl;
        }
    }
    // получить конфигурацию устройства
    libusb_get_config_descriptor(dev, 0, &config);
    cout << "Число конфигураций: " << (int)desc.bNumConfigurations <<endl;
    cout << "Класс устройства: " << usbClasses[(int)desc.bDeviceClass] <<endl;
    cout << "id производителя: " << (int)desc.idVendor <<endl;
    cout << "id устройства: " << (int)desc.idProduct <<endl;
    cout << "Число интерфейсов: " << (int)config->bNumInterfaces <<endl;
    for (int i = 0; i < (int)config->bNumInterfaces; i++) {
        inter = &config->interface[i];
        cout << "Интерфейс № " << i+1 << ":\n";
        cout << "\t" << "Число альтернативных настроек: " << inter->num_altsetting <<endl;
        for(int j = 0; j < inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            cout << "\t\t" << "Альтернативные настройки № " << j+1 <<endl;
            cout << "\t\t" << "Номер интерфейса: " << (int)interdesc->bInterfaceNumber <<endl;
            cout << "\t\t" << "Класс интерфейса: " << usbClasses[(int)interdesc->bInterfaceClass] <<endl;
            cout << "\t\t" << "Число конечных точек: " << (int)interdesc->bNumEndpoints <<endl;
            for(int k = 0; k < (int)interdesc->bNumEndpoints; k++) {
                epdesc = &interdesc->endpoint[k];
                cout << "\t\t\t" << "Конечная точка № " << k+1 << ":" <<endl;
                cout << "\t\t\t" << "Тип дескриптора: " << (int)epdesc->bDescriptorType <<endl;
                cout << "\t\t\t" << "Адрес конечной точки: " << (int)epdesc->bEndpointAddress <<endl;
            }
        }
    }
    libusb_free_config_descriptor(config);
    libusb_close(handle);
}

int main(){
    setlocale(LC_ALL, "Russian");
    libusb_device **devs;   //указатель на указатель на устройство, используется для получения списка устройств
    libusb_context *ctx = nullptr; //контекст сессии libusb
    int r;          //для возвращаемых значений
    ssize_t cnt;    //число найденных USB-устройств
    ssize_t i;      //индексная переменная цикла перебора всех устройств
    //инициализировать библиотеку libusb, открыть сессию работы с libusb
    r = libusb_init(&ctx);
    if (r < 0){
        fprintf(stderr, "Ошибка: инициализация не выполнена, код: %d.\n", r);
        return 1;
    }
    // задать уровень подробности отладочных сообщений
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);
    // получить список всех найденных USB- устройств
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0){
        fprintf(stderr, "Ошибка: список USB устройств не получен, код: %d.\n", r);
        return 1;
    }
    cout << "Найдено устройств: " << cnt <<endl;
    for (i = 0; i < cnt; i++) { // цикл перебора всех устройств
        cout << "Устройство: " << i+1 <<endl;
        printdev(devs[i]); // печать параметров устройства
        cout << "\n\n";
    }
    printf("===========================================================\n");
    //освободить память, выделенную функцией получения списка устройств
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx); //завершить работу с библиотекой libusb, закрыть сессию работы с libusb
    return 0;
}
