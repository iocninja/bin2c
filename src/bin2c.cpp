#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>



int wmain(int argc, wchar_t* argv[])
{
	if (argc < 2)
	{
		return 0;
	}

	const bool flat = argc == 2;

	const wchar_t* fileNameIn = argv[1];
	
	const wchar_t* arrayName = argc > 2 ? argv[2] : L"s_buffer";

	const uint32_t newline = argc > 3 ? _wtoi(argv[3]) : 8;

	FILE* file = _wfopen(fileNameIn, L"rb");
	
	if (file)
	{
		if (!flat)
		{
			wprintf(L"static uint8_t ");

			wprintf(L"%s[] =\n" , arrayName);

			wprintf(L"{\n");
		}

		fseek(file, 0, SEEK_END);

		const uint32_t plainSize = ftell(file);

		rewind(file);

		if (!flat)
		{
			wprintf(L"\t");
		}

		for (uint32_t i = 0; i < plainSize; i++)
		{
			if (!flat && i != 0 && i % newline == 0)
			{
				wprintf(L"\t");
			}

			uint8_t buffer;

			if (fread(&buffer, 1, 1, file) == 0)
			{
				break;
			}

			wprintf(flat ? L"%.2x" : L"0x%.2x", buffer);

			if (!flat && i < (plainSize - 1))
			{
				wprintf(L", ");
			}

			if (!flat && i != 0 && (i + 1) % newline == 0)
			{
				wprintf(L"\n");
			}
		}

		fclose(file);

		if (!flat)
		{
			wprintf(L"};\n");
		}
	}

	return 0;
}