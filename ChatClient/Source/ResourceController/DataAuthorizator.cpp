#include "../ResourceController/DataAuthorizator.h"

bool DataAuthorizator::checkInputNick(std::string str)
{
	if (str.size() < TextContentProperties::Max_Characters_Nick)
	{
		return true;
	}
		
	return false;
}

bool DataAuthorizator::checkInputMessage(std::string str, UserData user)
{
	if (str.size() + strlen(user.nick) < TextContentProperties::Max_Characters_Line * TextContentProperties::Max_Lines_In_Message)
	{
		return true;
	}	
	return false;
}
