import random
from collections import deque
import RSAKeysGenerator as math_calculations
import zlib

class EncryptionDecryptionPython:
    def __init__(self, key_size):
        self.public_key = None
        self.private_key = None
        self.key_size = key_size
        self.getRSAKeys(key_size)
        self.encrypted_chunk_size = self.key_size // 8
        self.original_data_length = None
        self.IV = None

    def getRSAKeys(self, m):
        prime_a, prime_b = math_calculations.generate_prime_pair(self.key_size)
        e = None
        n = 0
        while m > n:
            n = prime_a * prime_b
        ed = (prime_a - 1) * (prime_b - 1)
        for e in range(2, ed):
            if math_calculations.greatest_common_divisor(e, ed) == 1:
                break
        self.public_key = (n, e)
        modular_inverse = math_calculations.inverse_modulo(e, ed)
        self.private_key = int(modular_inverse)

    def ECBEncryption(self, data_to_encrypt):
        cipher_data = []
        after_iend_data = []
        self.original_data_length = len(data_to_encrypt)

        for i in range(0, len(data_to_encrypt), self.encrypted_chunk_size - 1):
            chunk_to_encrypt = bytes(data_to_encrypt[i:i + self.encrypted_chunk_size - 1])

            cipher_int = pow(int.from_bytes(chunk_to_encrypt, 'big'), self.public_key[1], self.public_key[0])
            cipher_bytes = cipher_int.to_bytes(self.encrypted_chunk_size, 'big')

            for j in range(self.encrypted_chunk_size - 1):
                cipher_data.append(cipher_bytes[j])
            after_iend_data.append(cipher_bytes[-1])
        cipher_data.append(after_iend_data.pop())

        return cipher_data, after_iend_data

    def concat_data(self, data, after_iend_data: deque):
        returned_data = []
        for i in range(0, len(data), self.encrypted_chunk_size - 1):
            returned_data.extend(data[i:i + self.encrypted_chunk_size - 1])
            returned_data.append(after_iend_data.popleft())
        returned_data.extend(after_iend_data)
        return returned_data

    def ECBDecryption(self, data, after_iend_data):
        data_to_decrypt = self.concat_data(data, deque(after_iend_data))
        decrypted_data = []

        for i in range(0, len(data_to_decrypt), self.encrypted_chunk_size):
            chunk_to_decrypt = bytes(data_to_decrypt[i:i + self.encrypted_chunk_size])
            decrypted_int = pow(int.from_bytes(chunk_to_decrypt, 'big'), self.private_key, self.public_key[0])
            if len(decrypted_data) + self.encrypted_chunk_size - 1 > self.original_data_length:
                decrypted_length_bytes = self.original_data_length - len(decrypted_data)
            else:
                decrypted_length_bytes = self.encrypted_chunk_size - 1

            decrypted_bytes = decrypted_int.to_bytes(decrypted_length_bytes, 'big')

            for byte in decrypted_bytes:
                decrypted_data.append(byte)

        return decrypted_data

    def CBCEncryption(self, data_to_encrypt):
        cipher_data = []
        after_iend_data = []
        self.original_data_length = len(data_to_encrypt)
        self.IV = random.getrandbits(self.key_size)
        prev = self.IV

        for i in range(0, len(data_to_encrypt), self.encrypted_chunk_size - 1):
            chunk_to_encrypt = bytes(data_to_encrypt[i:i + self.encrypted_chunk_size - 1])

            prev = prev.to_bytes(self.encrypted_chunk_size, 'big')
            prev = int.from_bytes(prev[:len(chunk_to_encrypt)], 'big')
            xor = int.from_bytes(chunk_to_encrypt, 'big') ^ prev

            cipher_int = pow(xor, self.public_key[1], self.public_key[0])
            prev = cipher_int
            cipher_bytes = cipher_int.to_bytes(self.encrypted_chunk_size, 'big')

            for j in range(self.encrypted_chunk_size - 1):
                cipher_data.append(cipher_bytes[j])
            after_iend_data.append(cipher_bytes[-1])
        cipher_data.append(after_iend_data.pop())

        return cipher_data, after_iend_data

    def CBCDecryption(self, data, after_iend_data):
        data_to_decrypt = self.concat_data(data, deque(after_iend_data))
        decrypted_data = []
        prev = self.IV

        for i in range(0, len(data_to_decrypt), self.encrypted_chunk_size):
            chunk_to_decrypt = bytes(data_to_decrypt[i:i + self.encrypted_chunk_size])
            decrypted_int = pow(int.from_bytes(chunk_to_decrypt, 'big'), self.private_key, self.public_key[0])

            if len(decrypted_data) + self.encrypted_chunk_size - 1 > self.original_data_length:
                decrypted_length_bytes = self.original_data_length - len(decrypted_data)
            else:
                decrypted_length_bytes = self.encrypted_chunk_size - 1

            prev = prev.to_bytes(self.encrypted_chunk_size, 'big')
            prev = int.from_bytes(prev[:decrypted_length_bytes], 'big')
            xor = prev ^ decrypted_int
            prev = int.from_bytes(chunk_to_decrypt, 'big')

            decrypted_bytes = xor.to_bytes(decrypted_length_bytes, 'big')

            for byte in decrypted_bytes:
                decrypted_data.append(byte)

        return decrypted_data

    def GetExtraData(self, cipher_data):
        cipher_data = deque(cipher_data)
        idat_data = []
        after_iend_data = []
        for i in range(self.original_data_length):
            idat_data.append(cipher_data.popleft())
        for i in range(len(cipher_data)):
            after_iend_data.append(cipher_data.popleft())

        return idat_data, after_iend_data


#ECB decompress
test = EncryptionDecryptionPython(1024)
png_file = open('buffer/IDATBytes', 'rb')
data = png_file.read()
data = zlib.decompress(data)
cipher, after_iend_data = test.ECBEncryption(data)
encrypted_data, after_iend_data2 = test.GetExtraData(cipher)
save = zlib.compress(bytes(encrypted_data))
encryptedFile = open('buffer/IDATBytesEncryptedECBDecompressed', 'wb')
encryptedFile.write(save)
encryptedFile.close()
decryptedFile = open('buffer/IDATBytesDecryptedECBDecompressed', 'wb')
decrypted_data = test.ECBDecryption(encrypted_data, (after_iend_data + after_iend_data2))
decryptedFile.write(zlib.compress(bytes(decrypted_data)))
decryptedFile.close()


#CBC decompress
png_file = open('buffer/IDATBytes', 'rb')
data = png_file.read()
data = zlib.decompress(data)
cipher, after_iend_data = test.CBCEncryption(data)
encrypted_data, after_iend_data2 = test.GetExtraData(cipher)
save = zlib.compress(bytes(encrypted_data))
encryptedFile = open('buffer/IDATBytesEncryptedCBCDecompressed', 'wb')
encryptedFile.write(save)
encryptedFile.close()
decryptedFile = open('buffer/IDATBytesDecryptedCBCDecompressed', 'wb')
decrypted_data = test.CBCDecryption(encrypted_data, (after_iend_data + after_iend_data2))
decryptedFile.write(zlib.compress(bytes(decrypted_data)))
decryptedFile.close()

#ECB compress
png_file = open('buffer/IDATBytes', 'rb')
data = png_file.read()
cipher, after_iend_data = test.ECBEncryption(data)
encrypted_data, after_iend_data2 = test.GetExtraData(cipher)
save = zlib.compress(bytes(encrypted_data))
encryptedFile = open('buffer/IDATBytesEncryptedECBCompressed', 'wb')
encryptedFile.write(save)
encryptedFile.close()
decryptedFile = open('buffer/IDATBytesDecryptedECBCompressed', 'wb')
decrypted_data = test.ECBDecryption(encrypted_data, (after_iend_data + after_iend_data2))
decryptedFile.write(bytes(decrypted_data))
decryptedFile.close()


#CBC compress
png_file = open('buffer/IDATBytes', 'rb')
data = png_file.read()
cipher, after_iend_data = test.CBCEncryption(data)
encrypted_data, after_iend_data2 = test.GetExtraData(cipher)
save = zlib.compress(bytes(encrypted_data))
encryptedFile = open('buffer/IDATBytesEncryptedCBCCompressed', 'wb')
encryptedFile.write(save)
encryptedFile.close()
decryptedFile = open('buffer/IDATBytesDecryptedCBCCompressed', 'wb')
decrypted_data = test.CBCDecryption(encrypted_data, (after_iend_data + after_iend_data2))
decryptedFile.write(bytes(decrypted_data))
decryptedFile.close()

