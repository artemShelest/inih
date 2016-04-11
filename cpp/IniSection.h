/* Macros to define section signature as a class.
   Usage:
   1. Define your section within a code:
   INIH_SECTION(confTest, testSection) // at the start of a section
   INIH_STR_ENTRY(str, "defaultString") // define different entry types,
   // missing entries will be returned as default values that you specify here
   INIH_INT_ENTRY(intValue, 42)
   INIH_REAL_ENTRY(realValue, 3.14)
   INIH_BOOL_ENTRY(boolValue, TRUE)
   INIH_SECTION_ENDS
   2. Use elsewhere:
   confTest ct(reader);
   long i = ct.intValue();
   bool b = ct.boolValue();
   double d = ct.realValue();
   std::string s = ct.str();

*/
#ifndef __INISECTION_H__
#define __INISECTION_H__

#include "INIReader.h"

class IniSectionBase
{
public:
	IniSectionBase(const INIReader& reader) :_reader(reader) {}
protected:
	const INIReader& _reader;
};

#define INIH_SECTION(STRUCT_NAME, INI_NAME) class STRUCT_NAME : public IniSectionBase { protected: const char* _section = #INI_NAME; \
	public: STRUCT_NAME(INIReader& reader) :IniSectionBase(reader){}
#define INIH_STR_ENTRY(NAME, DEFAULT) const std::string& NAME() const { static const std::string def(DEFAULT); return _reader.Get(_section, #NAME, def); }
#define INIH_INT_ENTRY(NAME, DEFAULT)  long NAME() const { return _reader.GetLong(_section, #NAME, DEFAULT); }
#define INIH_REAL_ENTRY(NAME, DEFAULT) double NAME() const { return _reader.GetReal(_section, #NAME, DEFAULT); }
#define INIH_BOOL_ENTRY(NAME, DEFAULT) bool NAME() const { return _reader.GetBoolean(_section, #NAME, DEFAULT); }
#define INIH_SECTION_ENDS };

#endif // __INISECTION_H__
