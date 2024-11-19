




address_to_three_bytes = lambda address : [(address >> z) & 0xFF for z in [16,8,0]]
three_bytes_as_str = lambda bytes : ' '.join(str(num) for num in bytes)

adr_bits = lambda a : three_bytes_as_str(address_to_three_bytes(a))


print(adr_bits(0x00000F))
