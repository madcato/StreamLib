

#import "C:\Archivos de Programa\Archivos Comunes\SYSTEM\ADO\MSADO15.DLL" rename("EOF", "adoEOF" )


inline void TESTHR(HRESULT x) {if FAILED(x) _com_issue_error(x);};

#include "PrepareCommand.h"

/// namespace stream
namespace stream
{
/// namespace sql
namespace sql
{


std::string GetAdoErrorDesc(_com_error e)
{
	std::string msg = "";
	if(!e.Description())
	{
		msg = e.ErrorMessage();
	}
	else
	{
		msg = (char*)e.Description();
	}

	return msg;
}

class ADOResultSet : public ResultSet
{
public:
	ADOResultSet(ADODB::_RecordsetPtr recordSet):m_recordSet(recordSet)
	{
	}

	void close()
	{
		try
		{
			m_recordSet->Close();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual long getLong(const std::string& column)
	{
		try
		{
			_variant_t InVar;

			InVar = m_recordSet->Fields->GetItem(column.c_str())->Value;
        
			if(InVar.vt == VT_NULL)
			{
				InVar = "{NULL}";
			}

			return (long)InVar;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual std::string getString(const std::string& column)
	{
		try
		{
			_variant_t InVar;

			InVar = m_recordSet->Fields->GetItem(column.c_str())->Value;

			if(InVar.vt == VT_NULL)
			{
				InVar = "{NULL}";
			}

			return (char*)(_bstr_t)InVar;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}
	
	virtual io::Blob<char> getBlob(const std::string& column)
	{
		io::Blob<char> blob;
		try
		{
		
			_variant_t InVar;
			_variant_t varChunk;
			
			ADODB::FieldPtr field = m_recordSet->Fields->GetItem(column.c_str());
			InVar = field->ActualSize;
			size_t size = (long)InVar;
			varChunk = field->GetChunk(size);

			blob.setLength(0);
			blob.resize(size);
			blob.attach((char*)varChunk.parray->pvData,size);			
			
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
		

		return blob;
		
	}

	virtual std::string getColumnName(const long& idColumn)
	{
		try
		{
			_variant_t InVar;

			if((idColumn >= m_recordSet->Fields->Count)||(idColumn < 0))
			{
				InVar = "";
			}
			else
			{

				ADODB::FieldPtr field = m_recordSet->Fields->GetItem(idColumn);
				if(field)
				{
					InVar = field->Name;
				}
				else
				{
					InVar = "";
				}
			}
			
			return (char*)(_bstr_t)InVar;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual void moveFirst()
	{
		try
		{
			m_recordSet->MoveFirst();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual void moveNext()
	{
		try
		{
			m_recordSet->MoveNext();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual void moveLast()
	{
		try
		{
			m_recordSet->MoveLast();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual bool eof()
	{
		try
		{
			if(m_recordSet->GetBOF() == VARIANT_BOOL(-1))
			{
				return true;
			}

			if(m_recordSet->GetadoEOF() == -1)
			{
				return true;
			}

			return false;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual ulong getColumnCount()
	{
		return m_recordSet->Fields->Count;
	}

	virtual std::string getString(const long columnIndex)
	{
		try
		{
			_variant_t InVar;

			InVar = m_recordSet->Fields->GetItem(columnIndex)->Value;

			if(InVar.vt == VT_NULL)
			{
				InVar = "{NULL}";
			}

			return (char*)(_bstr_t)InVar;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}
	
	virtual bool isNull(const std::string& column)
	{
		try
		{
			_variant_t InVar;

			InVar = m_recordSet->Fields->GetItem(column.c_str())->Value;

			if(InVar.vt == VT_NULL)
			{
				return true;
			}

			return false;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual bool isNull(const long columnIndex)
	{
		try
		{
			_variant_t InVar;

			InVar = m_recordSet->Fields->GetItem(columnIndex)->Value;

			if(InVar.vt == VT_NULL)
			{
				return true;
			}

			return false;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

private:
	ADODB::_RecordsetPtr m_recordSet;
};

class ADOPreparedStatement : public PreparedStatement
{
public:
	ADOPreparedStatement(const std::string& sql,ADODB::_ConnectionPtr pConnection):m_pConnection(pConnection)
	{
		m_command.setCommand(sql);
	}

	virtual ~ADOPreparedStatement()
	{
	}

	std::auto_ptr<ResultSet> executeQuery()
	{
		try
		{
			ADODB::_RecordsetPtr adoRs = NULL;

			TESTHR(adoRs.CreateInstance(__uuidof(ADODB::Recordset)));
			adoRs->Open( m_command.getFinalCommand().c_str(),
						  _variant_t((IDispatch *)m_pConnection,true),
						  ADODB::adOpenForwardOnly, ADODB::adLockReadOnly, ADODB::adCmdText );

			std::auto_ptr<ResultSet> result(new ADOResultSet(adoRs));
			return result;
		
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}		
	}

	long execute()
	{
		try
		{
			_variant_t rowsAffected((long)-1);
			m_pConnection->Execute(m_command.getFinalCommand().c_str(),&rowsAffected,0);
			
			return (long)rowsAffected;
		
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}				
	}


private:
	ADODB::_ConnectionPtr m_pConnection;	
};

class ADOConnection : public Connection
{
public:
	ADOConnection(const std::string& connectionString)
	{
		try
		{
			TESTHR(m_pConnection.CreateInstance(__uuidof(ADODB::Connection)));
			m_pConnection->Open(connectionString.c_str(),"","",ADODB::adConnectUnspecified);
	
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}				
	}

	virtual ~ADOConnection()
	{
	}

	ADODB::_ConnectionPtr getConnection()
	{
		return m_pConnection;
	}

	std::auto_ptr<PreparedStatement> prepareStatement(const std::string& sql)
	{
		std::auto_ptr<PreparedStatement> returnvalue(new ADOPreparedStatement(sql,getConnection()));

		return returnvalue;
	}

	virtual void close()
	{
		try
		{
			m_pConnection->Close();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual void startTransaction()
	{
		try
		{
			long nesting = m_pConnection->BeginTrans();
			int a = 0;
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual void commit()
	{
		try
		{
			m_pConnection->CommitTrans();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}

	virtual void rollback()
	{
		try
		{
			m_pConnection->RollbackTrans();
		}catch(_com_error e)
		{
			throw new exceptions::SQLException(GetAdoErrorDesc(e));
		}
	}



private:
	ADODB::_ConnectionPtr m_pConnection;
};

} // namespace sql

} // namespace stream