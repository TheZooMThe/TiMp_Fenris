#include "sha384.h"

// Конструктор класса SHA384
SHA384::SHA384() {}

// Деструктор класса SHA384
SHA384::~SHA384() {}

// Метод хеширования входного массива байтов
QByteArray SHA384::hash(const QByteArray& input) {
    quint64 nBuffer;
    uint64** buffer;
    uint64* h = new uint64[HASH_LEN];

    buffer = preprocess(input, nBuffer); // Предобработка входных данных
    process(buffer, nBuffer, h); // Обработка предобработанных данных

    freeBuffer(buffer, nBuffer); // Освобождение памяти, выделенной под буфер
    return digest(h); // Возврат хеша
}

// Метод предобработки входных данных
quint64** SHA384::preprocess(const QByteArray& input, quint64& nBuffer) {
    size_t mLen = input.size(); // Размер входного массива байтов
    size_t l = mLen * CHAR_LEN_BITS; // Длина входных данных в битах
    size_t k = (896 - 1 - l) % MESSAGE_BLOCK_SIZE; // Вычисление величины заполнения
    nBuffer = (l + 1 + k + 128) / MESSAGE_BLOCK_SIZE; // Вычисление количества блоков

    uint64** buffer = new uint64*[nBuffer]; // Выделение памяти под буфер

    for (size_t i = 0; i < nBuffer; i++) {
        buffer[i] = new uint64[SEQUENCE_LEN]; // Выделение памяти для каждого блока
    }

    uint64 in;
    size_t index;

    // Заполнение буфера входными данными
    for (size_t i = 0; i < nBuffer; i++) {
        for (size_t j = 0; j < SEQUENCE_LEN; j++) {
            in = 0x0ULL;
            for (size_t k = 0; k < WORD_LEN; k++) {
                index = i * 128 + j * 8 + k;
                if (index < mLen) {
                    in = in << 8 | (uint64)input[index];
                } else if (index == mLen) {
                    in = in << 8 | 0x80ULL;
                } else {
                    in = in << 8 | 0x0ULL;
                }
            }
            buffer[i][j] = in;
        }
    }

    // Добавление длины входных данных в последние два 64-битных блока
    appendLen(l, buffer[nBuffer - 1][SEQUENCE_LEN - 1], buffer[nBuffer - 1][SEQUENCE_LEN - 2]);
    return buffer;
}

// Метод обработки данных
void SHA384::process(uint64** buffer, quint64 nBuffer, uint64* h) {
    uint64 s[WORKING_VAR_LEN];
    uint64 w[MESSAGE_SCHEDULE_LEN];

    memcpy(h, hPrime, WORKING_VAR_LEN * sizeof(uint64)); // Копирование начальных значений хеша

    for (size_t i = 0; i < nBuffer; i++) {
        memcpy(w, buffer[i], SEQUENCE_LEN * sizeof(uint64)); // Копирование блока в расширяемый массив

        for (size_t j = 16; j < MESSAGE_SCHEDULE_LEN; j++) {
            w[j] = w[j - 16] + sig0(w[j - 15]) + w[j - 7] + sig1(w[j - 2]); // Подготовка расширяемого массива
        }

        memcpy(s, h, WORKING_VAR_LEN * sizeof(uint64)); // Копирование рабочих переменных

        for (size_t j = 0; j < MESSAGE_SCHEDULE_LEN; j++) {
            uint64 temp1 = s[7] + Sig1(s[4]) + Ch(s[4], s[5], s[6]) + k[j] + w[j]; // Вычисление временных переменных
            uint64 temp2 = Sig0(s[0]) + Maj(s[0], s[1], s[2]);

            s[7] = s[6];
            s[6] = s[5];
            s[5] = s[4];
            s[4] = s[3] + temp1;
            s[3] = s[2];
            s[2] = s[1];
            s[1] = s[0];
            s[0] = temp1 + temp2;
        }

        for (size_t j = 0; j < WORKING_VAR_LEN; j++) {
            h[j] += s[j]; // Вычисление промежуточных значений хеша
        }
    }
}

// Метод добавления длины входных данных
void SHA384::appendLen(quint64 l, uint64& lo, uint64& hi) {
    lo = l;
    hi = 0x00ULL;
}

// Метод вычисления финального хеша
QByteArray SHA384::digest(uint64* h) {
    QByteArray result;
    QDataStream stream(&result, QIODevice::WriteOnly);

    for (size_t i = 0; i < OUTPUT_LEN; i++) {
        stream << h[i]; // Запись промежуточных значений в результирующий массив байтов
    }

    delete[] h; // Освобождение памяти, выделенной под массив промежуточных значений
    return result.toHex(); // Преобразование результирующего массива байтов в строку в формате hex и возврат
}

// Метод освобождения памяти, выделенной под буфер
void SHA384::freeBuffer(uint64** buffer, quint64 nBuffer) {
    for (size_t i = 0; i < nBuffer; i++) {
        delete[] buffer[i]; // Освобождение памяти, выделенной для каждого блока
    }

    delete[] buffer; // Освобождение памяти, выделенной для массива блоков
}

