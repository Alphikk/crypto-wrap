import ctypes
import base64

def get_key(s1,s2):
    """TODO: THINK ABOUT ERROR HANDLING  """
    if len(s1) < 32 and len(s2) < 32:
        return None
    cr_k_lib = ctypes.CDLL('./createkeys.so') #TODO: RENAME .so module in future
    cr_k_lib.createAesKey.restype = ctypes.c_ulong
    num = 32 #CONST
    resultbuf = (ctypes.c_ubyte*num)()
    bufptr = ctypes.cast(resultbuf, ctypes.POINTER(ctypes.c_ubyte))

    cr_k_lib.createAesKey.argtypes = [ctypes.POINTER(ctypes.c_ubyte), \
                                    ctypes.c_uint, \
                                    ctypes.POINTER(ctypes.c_ubyte), \
                                    ctypes.c_uint, \
                                    ctypes.POINTER(ctypes.c_ubyte), \
                                    ctypes.c_uint, \
                                    ctypes.c_uint]

    bs1 = bytearray(s1,"utf-8")
    len_bs1 = len(bs1)
    c_bs1 = (ctypes.c_ubyte*len_bs1)(*list(bs1))

    bs2 = bytearray(s2,"utf-8")
    len_bs2 = len(bs2)
    c_bs2 = (ctypes.c_ubyte*len_bs2)(*list(bs2))

    response =  cr_k_lib.createAesKey(bufptr,num,c_bs1,len_bs1,c_bs2,len_bs2,1)
    if response != 0:
        return None
    result = bytearray()
    ## Add first byte to result 
    result.append(bufptr.contents.value)
    incrementPtr = ctypes.cast(ctypes.pointer(bufptr), ctypes.POINTER(ctypes.c_void_p))
    
    ## INCREMENT POINTER
    for i in range(num-1):
        incrementPtr.contents.value += ctypes.sizeof(bufptr._type_)
        result.append(bufptr.contents.value)

    key = base64.b64encode(result).decode("utf-8")
    return key