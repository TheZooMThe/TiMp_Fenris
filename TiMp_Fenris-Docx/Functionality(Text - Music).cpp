#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sndfile.hh>
#include <cstdlib> // Для функции system для очистки экрана
#include <chrono>  // Для задержки
#include <thread>  // Для задержки

class AudioSteganography {
public:
    // Встраивание сообщения в аудиофайл
    bool embedMessage(const std::string& audioFilePath, const std::string& outputFilePath, const std::string& message) {
        SndfileHandle file(audioFilePath);
        if (file.error()) {
            std::cerr << "Не удалось прочитать аудиофайл." << std::endl;
            return false;
        }

        // Проверка формата файла
        if (file.format() != (SF_FORMAT_WAV | SF_FORMAT_PCM_16) &&
            file.format() != (SF_FORMAT_FLAC) &&
            file.format() != (SF_FORMAT_OGG | SF_FORMAT_VORBIS)) {
            std::cerr << "Поддерживаются только форматы WAV, FLAC и OGG/Vorbis." << std::endl;
            return false;
        }

        // Преобразование длины сообщения и самого сообщения в двоичный формат
        std::string binaryLength = intToBinary(message.size(), 32);
        std::string binaryMessage = stringToBinary(message);
        std::string binaryData = binaryLength + binaryMessage;

        // Проверка, что сообщение помещается в аудиофайл
        if (binaryData.size() > file.frames() * file.channels()) {
            std::cerr << "Сообщение слишком длинное для встраивания в аудиофайл." << std::endl;
            return false;
        }

        // Встраивание каждого бита данных в младший значащий бит каждого значения
        std::vector<short> audioData(file.frames() * file.channels());
        file.read(reinterpret_cast<char*>(audioData.data()), audioData.size());
        for (size_t i = 0; i < binaryData.size(); ++i) {
            audioData[i] = (audioData[i] & 0xFFFFFE00) | (binaryData[i] - '0');
        }

        // Запись измененного аудиофайла в выходной файл
        SndfileHandle outputFile(outputFilePath, SFM_WRITE, file.format(), file.channels(), file.samplerate());
        outputFile.write(reinterpret_cast<char*>(audioData.data()), audioData.size());

        return true;
    }

    // Извлечение сообщения из аудиофайла
    std::string extractMessage(const std::string& audioFilePath) {
        SndfileHandle file(audioFilePath);
        if (file.error()) {
            std::cerr << "Не удалось прочитать аудиофайл." << std::endl;
            return "";
        }

        // Проверка формата файла
        if (file.format() != (SF_FORMAT_WAV | SF_FORMAT_PCM_16) &&
            file.format() != (SF_FORMAT_FLAC) &&
            file.format() != (SF_FORMAT_OGG | SF_FORMAT_VORBIS)) {
            std::cerr << "Поддерживаются только форматы WAV, FLAC и OGG/Vorbis." << std::endl;
            return "";
        }

        // Извлечение длины сообщения (первые 32 бита)
        std::string binaryLength;
        for (size_t i = 0; i < 32; ++i) {
            short sample;
            file.read(&sample, 1);
            binaryLength += (sample & 1) ? '1' : '0';
        }
        size_t messageLength = binaryToInt(binaryLength);

        // Извлечение самого сообщения на основе длины
        std::string binaryMessage;
        for (size_t i = 32; i < 32 + messageLength * 8; ++i) {
            short sample;
            file.read(&sample, 1);
            binaryMessage += (sample & 1) ? '1' : '0';
        }

        // Преобразование двоичного представления сообщения обратно в строку
        return binaryToString(binaryMessage);
    }

private:
    // Преобразование строки в двоичный формат
    std::string stringToBinary(const std::string& message) {
        std::string binaryMessage;
        for (char c : message) {
            for (int i = 7; i >= 0; --i) {
                binaryMessage += ((c >> i) & 1) ? '1' : '0';
            }
        }
        return binaryMessage;
    }

    // Преобразование двоичного сообщения обратно в строку
    std::string binaryToString(const std::string& binaryMessage) {
        std::string message;
        for (size_t i = 0; i < binaryMessage.size(); i += 8) {
            char c = 0;
            for (size_t j = 0; j < 8; ++j) {
                c = (c << 1) | (binaryMessage[i + j] - '0');
            }
            message += c;
        }
        return message;
    }

    // Преобразование целого числа в двоичный формат
    std::string intToBinary(int num, int bits) {
        std::string binary;
        for (int i = bits - 1; i >= 0; --i) {
            binary += ((num >> i) & 1) ? '1' : '0';
        }
        return binary;
    }

    // Преобразование двоичного числа в целое
    int binaryToInt(const std::string& binary) {
        int num = 0;
        for (size_t i = 0; i < binary.size(); ++i) {
            num = (num << 1) | (binary[i] - '0');
        }
        return num;
    }
};

int main() {
    AudioSteganography steg;
    std::string audioFilePath, message;

    while (true) {
        std::cout << "Выберите действие:\n";
        std::cout << "1. Вставить сообщение в аудиофайл\n";
        std::cout << "2. Извлечь сообщение из аудиофайла\n";
        std::cout << "3. Выход\n";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера после ввода числа

        if (choice == 1) {
            std::cout << "Введите путь к аудиофайлу:\n";
            std::getline(std::cin, audioFilePath);
            std::cout << "Введите сообщение:\n";
            std::getline(std::cin, message);

            std::string outputFilePath = "output.wav"; // или output.flac, output.ogg
            // Встраивание сообщение в аудиофайл
            if (steg.embedMessage(audioFilePath, outputFilePath, message)) {
                std::cout << "Сообщение успешно внедрено" << std::endl;
            }
            else {
                std::cout << "Ошибка в процессе внедрения" << std::endl;
            }

            // Задержка перед очисткой консоли
            std::this_thread::sleep_for(std::chrono::seconds(3));
            // Очистка экрана консоли
            system("clear"); // Для Unix-like систем
            // system("cls"); // Для Windows
        }
        else if (choice == 2) {
            std::cout << "Введите путь к аудиофайлу:\n";
            std::getline(std::cin, audioFilePath);

            // Извлечение сообщения из аудиофайла
            std::string extractedMessage = steg.extractMessage(audioFilePath);
            if (!extractedMessage.empty()) {
                std::cout << "Извлеченное сообщение: " << extractedMessage << std::endl;
            }
            else {
                std::cout << "Ошибка в процессе извлечения" << std::endl;
            }

            // Задержка перед очисткой консоли
            std::this_thread::sleep_for(std::chrono::seconds(3));
            // Очистка экрана консоли
            system("clear"); // Для Unix-like систем
            // system("cls"); // Для Windows
        }
        else if (choice == 3) {
            break;
        }
        else {
            std::cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    }

    return 0;
}