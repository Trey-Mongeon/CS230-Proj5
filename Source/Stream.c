//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Trey Mongeon (tmongeon), Doug Schilling (dschilling)
// Project:		Project 2
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Stream.h"
#include "errno.h"
#include "string.h"
#include "Trace.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
static char tokenBuffer[1024];
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Open a file for reading.
// (NOTE: Use fopen_s() with the "rt" option.)
// (NOTE: You must generate the following trace message if the file was not opened successfully:
//	  TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
//	  Where errorMsg is a char array containing the error message obtained using strerror_s().)
// Params:
//	 filePath = The file to be opened for reading.
// Returns:
//	 NULL if filePath is NULL or the file could not be opened.
//	 Pointer to a FILE object if the file was opened successfully.
Stream StreamOpen(const char* filePath)
{
	if (filePath == NULL)
	{
		return NULL;
	}

	Stream filePtr = 0;
	fopen_s(&filePtr, filePath, "rt");
	if(!filePtr)
	{
		char errorMsg[256] = { 0 };
		strerror_s(errorMsg, _countof(errorMsg), errno);

		TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);

		return NULL;
	}
	else
	{
		return filePtr;
	}
}


// Read the data for a Color from a stream.
// (NOTE: Verify that the stream and color pointers are valid first.)
// (HINT: Use StreamReadFloat() to read the RGBA values, in sequence.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream and color pointers are both valid,
//	   then read the RGBA components, in sequence,
//	   else fill the RGBA components with 0.
//		 (optionally, write an error message to the trace log).
void StreamReadColor(Stream stream, DGL_Color* color)
{
	if (stream && color)
	{
		color->r = StreamReadFloat(stream);
		color->g = StreamReadFloat(stream);
		color->b = StreamReadFloat(stream);
		color->a = StreamReadFloat(stream);
	}
	else if (color)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
		color->a = 0;
	}
}


// Read a single integer from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 0 if the stream was not opened succesfully;
//	 otherwise, an integer value read from the file.
int StreamReadInt(Stream stream)
{
	if (stream)
	{
		int readInt;
		fscanf_s(stream, "%d", &readInt);
		return readInt;
	}
	else
	{
		return 0;
	}
}

// Read a single float from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for a float.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream was opened succesfully,
//	   then return a float value read from the file,
//	   else return 0.
float StreamReadFloat(Stream stream)
{
	if (stream)
	{
		float readFlt;
		fscanf_s(stream, "%f", &readFlt);
		return readFlt;
	}
	else
	{
		return 0;
	}
}

// Read the data for a Vector2D from a stream.
// (NOTE: Verify that the stream and vector pointer are valid first.)
// (HINT: Use StreamReadFloat() to read the x and y values, in sequence.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream and vector pointer are both valid,
//	   then fill the vector with two float values (x & y),
//	   else do nothing (optionally, write an error message to the trace log).
void StreamReadVector2D(Stream stream, Vector2D* vector)
{
	if (stream && vector)
	{
			vector->x = StreamReadFloat(stream);
			vector->y = StreamReadFloat(stream);
		
	}
}

// Read a token (a single word) from a file.
// Suggested steps:
//	 - Set the first value in tokenBuffer to 0
//	 - If the stream was opened successfully,
//	   - Read a string ("%s") into tokenBuffer using fscanf_s()
//	 - Return tokenBuffer
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 Pointer to tokenBuffer
const char* StreamReadToken(Stream stream)
{
	tokenBuffer[0] = 0;

	if (stream)
	{
		
		fscanf_s(stream, "%s", tokenBuffer, (unsigned)_countof(tokenBuffer));
		
	}
	return tokenBuffer;
}


// Read a single boolean value from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 If the stream was opened succesfully,
//	   then return a boolean value read from the file as an integer,
//	   else return 0.
bool StreamReadBoolean(Stream stream)
{
	if (stream)
	{
		int readBool = 0;
		fscanf_s(stream, "%d", &readBool);
		return readBool;
	}
	else
	{
		return 0;
	}
}


// Close an opened stream.
// (NOTE: Do not attempt to close the stream if the pointer is null.)
// (PRO TIP: Avoid dangling pointers by setting the FILE pointer to NULL.)
// Params:
//	 stream = The file stream to be closed.
void StreamClose(Stream* stream)
{
	if (*stream)
	{
		fclose(*stream);
		*stream = NULL;
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

