#ifndef __ENTRY2_H
#define __ENTRY2_H

/// namespace stream
namespace stream
{
/**
	Utilities
*/
namespace util
{
class Parseador2;


#define PARAM_NOTRATADO "PARSEADOR_PARAMETRO_NO_TRATADO"
#define PARAM_NO_VALUE "PARAMETRO_SINVALOR"
#define NO_DEFAULT_ENTRY "NO_HAY_DEFAULT_ENTRY"
#define ERROR_TRATAMIENTO "HAY_ERROR_DE_TRATAMIENTO"

/**
	Interface that must be implemented by the objects that requires access to the
	command line parameters.
	@see Parseador2
*/
class Entry2
{
public:
	/// Method called by the Parseador2 to pass the parameters and the values.
	virtual bool Trata(std::string parametro,std::string value) = 0;

	/** Method called by the Parseador2 to retrieve the error description.
		@retrun "" to indicate that no error was produced.
	*/
	virtual std::string GetError() = 0;

	

};

} // namespace util

}

#endif __ENTRY2_H