#include "VigenereCipher.h"

VigenereCipher::VigenereCipher(const QByteArray &key) : key(key) {}

void VigenereCipher::setKey(const QByteArray &newKey) {
    // Functio ad clavem mutandam
    key = newKey;
}

bool VigenereCipher::isAlpha(char c) {
    // Functio ad verificandum an character sit litera
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

QByteArray VigenereCipher::generateKey(const QByteArray &text) {
    // Functio ad generandam clavem ex textu dato
    QByteArray generatedKey;
    int keyIndex = 0;
    for (int i = 0; i < text.size(); ++i) {
        if (isAlpha(text[i])) {
            // Si character est litera
            while (!isAlpha(key[keyIndex % key.size()])) {
                keyIndex++;
            }
            // Appende literam clavis ad clavem generatam
            generatedKey.append(key[keyIndex % key.size()]);
            keyIndex++;
        } else {
            // Si character non est litera, appende ipsum ad clavem generatam
            generatedKey.append(text[i]);
        }
    }
    return generatedKey;
}

char VigenereCipher::shiftChar(char c, char keyChar) {
    // Functio ad characterem movere secundum clavem
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' + (keyChar - (keyChar >= 'a' ? 'a' : 'A'))) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' + (keyChar - (keyChar >= 'a' ? 'a' : 'A'))) % 26;
    }
    return c;
}

char VigenereCipher::unshiftChar(char c, char keyChar) {
    // Functio ad characterem demovere secundum clavem
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' - (keyChar - (keyChar >= 'a' ? 'a' : 'A')) + 26) % 26;
    } else if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' - (keyChar - (keyChar >= 'a' ? 'a' : 'A')) + 26) % 26;
    }
    return c;
}

QByteArray VigenereCipher::encrypt(const QByteArray &plaintext) {
    // Functio ad textum encryptandum
    QByteArray result;
    QByteArray generatedKey = generateKey(plaintext);
    for (int i = 0; i < plaintext.size(); ++i) {
        // Movere singulos characteres secundum clavem et appensum resultati
        result.append(shiftChar(plaintext[i], generatedKey[i]));
    }
    return result;
}

QByteArray VigenereCipher::decrypt(const QByteArray &ciphertext) {
    // Functio ad textum decryptandum
    QByteArray result;
    QByteArray generatedKey = generateKey(ciphertext);
    for (int i = 0; i < ciphertext.size(); ++i) {
        // Demovere singulos characteres secundum clavem et appensum resultati
        result.append(unshiftChar(ciphertext[i], generatedKey[i]));
    }
    return result;
}
