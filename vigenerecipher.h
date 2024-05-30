#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QByteArray>

class VigenereCipher {
public:
    VigenereCipher(const QByteArray &key);
    void setKey(const QByteArray &newKey);
    QByteArray encrypt(const QByteArray &plaintext);
    QByteArray decrypt(const QByteArray &ciphertext);

private:
    QByteArray key;
    QByteArray generateKey(const QByteArray &text);
    char shiftChar(char c, char keyChar);
    char unshiftChar(char c, char keyChar);
    bool isAlpha(char c);
};

#endif // VIGENERECIPHER_H
