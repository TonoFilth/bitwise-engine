////////////////////////////////////////////////////////////////////////////////
//  Inline functions & templates
////////////////////////////////////////////////////////////////////////////////
F32 SwapF32(F32 value)
{
	F32 result;
    
	char* toConvert = (char*) &value;
    char* toReturn  = (char*) &result;

    toReturn[0] = toConvert[3];
    toReturn[1] = toConvert[2];
    toReturn[2] = toConvert[1];
    toReturn[3] = toConvert[0];

   return result;
}

// -----------------------------------------------------------------------------

F64 SwapF64(F64 value)
{
	F64 result;

    char* toConvert = (char*) &value;
    char* toReturn  = (char*) &result;

    toReturn[0] = toConvert[7];
    toReturn[1] = toConvert[6];
    toReturn[2] = toConvert[5];
    toReturn[3] = toConvert[4];
    toReturn[4] = toConvert[3];
    toReturn[5] = toConvert[2];
    toReturn[6] = toConvert[1];
    toReturn[7] = toConvert[0];

   return result;
}