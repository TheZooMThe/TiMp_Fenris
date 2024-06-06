#include "vigenerecipher.h"

VigenereCipher::VigenereCipher(const QByteArray &key) : key(key) {}

void VigenereCipher::setKey(const QByteArray &newKey) {
    key = newKey;
}

bool VigenereCipher::isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

QByteArray VigenereCipher::generateKey(const QByteArray &text) {
    QByteArray generatedKey;
    int keyIndex = 0;
    for (int i = 0; i < text.size(); ++i) {
        if (isAlpha(text[i])) {
            while (!isAlpha(key[keyIndex % key.size()])) {
                keyIndex++;
            }
            generatedKey.append(key[keyIndex % key.size()]);
            keyIndex++;
        } else {
            generatedKey.append(text[i]);
        }
    }
    return generatedKey;
}

char VigenereCipher::shiftChar(char c, char keyChar) {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + (keyChar - (keyChar >= 'a' ? 'a' : 'A'))) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + (keyChar - (keyChar >= 'a' ? 'a' : 'A'))) % 26;
    }
    return c;
}

char VigenereCipher::unshiftChar(char c, char keyChar) {
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' - (keyChar - (keyChar >= 'a' ? 'a' : 'A')) + 26) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' - (keyChar - (keyChar >= 'a' ? 'a' : 'A')) + 26) % 26;
    }
    return c;
}

QByteArray VigenereCipher::encrypt(const QByteArray &plaintext) {
    QByteArray result;
    QByteArray generatedKey = generateKey(plaintext);
    for (int i = 0; i < plaintext.size(); ++i) {
        result.append(shiftChar(plaintext[i], generatedKey[i]));
    }
    return result;


    // return plaintext;
}

QByteArray VigenereCipher::decrypt(const QByteArray &ciphertext) {

    QByteArray result;
    QByteArray generatedKey = generateKey(ciphertext);
    for (int i = 0; i < ciphertext.size(); ++i) {
        result.append(unshiftChar(ciphertext[i], generatedKey[i]));
    }
    return result;

    // return ciphertext;
}
