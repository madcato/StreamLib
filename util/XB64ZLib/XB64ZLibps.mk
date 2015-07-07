
XB64ZLibps.dll: dlldata.obj XB64ZLib_p.obj XB64ZLib_i.obj
	link /dll /out:XB64ZLibps.dll /def:XB64ZLibps.def /entry:DllMain dlldata.obj XB64ZLib_p.obj XB64ZLib_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del XB64ZLibps.dll
	@del XB64ZLibps.lib
	@del XB64ZLibps.exp
	@del dlldata.obj
	@del XB64ZLib_p.obj
	@del XB64ZLib_i.obj
