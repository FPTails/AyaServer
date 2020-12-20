set CURRENT_PATH=%~dp0
echo %CURRENT_PATH%

mkdir %CURRENT_PATH%\Client_To_Server_Packet

protoc -I%CURRENT_PATH% --cpp_out=%CURRENT_PATH%\Client_To_Server_Packet %CURRENT_PATH%Client_To_Server_Packet.proto