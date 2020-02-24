#include "cipher.h"

#define UPPER_CASE(r) ((r) - ('a' - 'A'))

struct Cipher::CipherCheshire {
    string cipherText;
};

Cipher::Cipher()
{
    smile = new CipherCheshire;
    smile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
}
Cipher::Cipher(string in)
{
    smile = new CipherCheshire;
    smile->cipherText = in;
}
string Cipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(raw[i] == ' ') {
            pos = 26;
        } else if(raw[i] >= 'a') {
            pos = raw[i] - 'a';
        } else {
            pos = raw[i] - 'A';
            upper = 1;
        }
        if(upper) {
            retStr += UPPER_CASE(smile->cipherText[pos]);
        } else {
            retStr += smile->cipherText[pos];
        }
    }
    cout << "Done" << endl;

    return retStr;
}

string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrpyting..." << endl;
    // TODO: Fill in code here
    for (unsigned int i = 0; i < enc.size(); i++)
    {
	unsigned int pos;
	bool upper = false;

	if (enc[i] == ' ')
	    pos = 26;
	else if (enc[i] >= 'a')
	    pos = enc[i] - 'a' + 1;
	else {
	    pos = enc[i] - 'A' + 1;
	    upper = 1;
	}

	if (upper)
	    retStr += UPPER_CASE(smile->cipherText[pos]);
	else
	    retStr += smile->cipherText[pos];
	}

    cout << "Done" << endl;

    return retStr;
}




struct CaesarCipher::CaesarCipherCheshire : CipherCheshire {
     int rot;
};

CaesarCipher::CaesarCipher()
{
    // TODO: Fill in code here
    CaesarSmile = new CaesarCipherCheshire;
    CaesarSmile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
}

CaesarCipher::CaesarCipher(string in, int rot)
{
    // TODO: Fill in code here
    CaesarSmile = new CaesarCipherCheshire;
    CaesarSmile->cipherText = in;
    CaesarSmile->rot = rot;
}

string CaesarCipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    // TODO: Fill in code here
    for (unsigned int i = 0; i < raw.size(); i++)
    {
	unsigned int pos;
	bool upper = false;
	int shift = CaesarSmile->rot % 27;

	if (raw[i] == ' ')
	    pos = ((26 + shift) % 27);
	else if (raw[i] >= 'a')
	    pos = ((raw[i] + shift - 'a' + 27) % 27);
	else {
	    pos = ((raw[i] + shift - 'A' + 27) % 27);
	    upper = 1;
	}

	if (upper)
	    retStr += UPPER_CASE(CaesarSmile->cipherText[pos]);
	else
	    retStr += CaesarSmile->cipherText[pos];
    }

    cout << "Done" << endl;

    return retStr;
}

string CaesarCipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrpyting..." << endl;
    // TODO: Fill in code here
    for (unsigned int i = 0; i < enc.size(); i++)
    {
	unsigned int pos = 0;
	bool upper = false;
	int shift = CaesarSmile->rot % 27;

	if (enc[i] == ' ') {
	    pos = ((26 + shift) % 27);
	} else if (enc[i] >= 'a') {
	    pos = ((enc[i] - shift - 'a' + 27) % 27) + 1;
	} else {
	    pos = ((enc[i] - shift - 'A' + 27) % 27) + 1;
	    upper = 1;
	}

	if (upper)
	    retStr += UPPER_CASE(CaesarSmile->cipherText[pos]);
	else
	    retStr += CaesarSmile->cipherText[pos];
    }

    cout << "Done" << endl;

    return retStr;
}


