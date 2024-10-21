#!/usr/bin/env python3

def decrypt(encrypted):
    decrypted = ""
    for i, char in enumerate(encrypted):
        # ord() converts a character to its ASCII value
        # chr() converts an ASCII value back to a character
        decrypted += chr(ord(char) - i)
    return decrypted

# Read the encrypted content from the token file
with open('token', 'rb') as f:
    encrypted = f.read().strip()

# Decrypt the content
decrypted = decrypt(encrypted.decode('latin-1'))

print(f"Decrypted: {decrypted}")
