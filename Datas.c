#include "Crack.h"

char	szAlphabet[1024]	;

//char		szAlphabet_Accents[]	=	"âäçèéêëîïôöûü" ;
char		szAlphabet_Binary[]		=	"01" ;
char		szAlphabet_Clc[]		=	"bcdfghjklmnpqrstvwxz" ;
char		szAlphabet_Cuc[]		=	"BCDFGHJKLMNPQRSTVWXZ" ;
char		szAlphabet_Llc[]		=	"abcdefghijklmnopqrstuvwxyz" ;
char		szAlphabet_Luc[]		=	"ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
char		szAlphabet_Morse[]		=	"-." ;
char		szAlphabet_Numbers[]	=	"0123456789" ;
char		szAlphabet_Operators[]	=	"%*+-/" ;
char		szAlphabet_Signs[]		=	" !\"#$%&'()*+,-/:;<=>\?@[\\]_{}" ;
char		szAlphabet_Vlc[]		=	"aeiouy" ;
char		szAlphabet_Vuc[]		=	"AEIOUY" ;

ALPHABET	Alphabet_001			=	{  1,0,1,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Vowels Upper Case","AEIOUY"} ;
ALPHABET	Alphabet_002			=	{  2,0,1,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Vowels Lower Case","aeiouy"} ;
ALPHABET	Alphabet_003			=	{  3,0,2,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Vowels Lower Case + Vowels Upper Case","aeiouyAEIOUY"} ;
ALPHABET	Alphabet_004			=	{  4,0,1,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Signs"," !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_005			=	{  5,0,2,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Signs + Vowels Upper Case"," !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_006			=	{  6,0,2,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Signs + Vowels Lower Case"," !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_007			=	{  7,0,3,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Signs + Vowels Lower Case + Vowels Upper Case"," !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_008			=	{  8,0,1,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Operators","+-*/%"} ;
ALPHABET	Alphabet_009			=	{  9,0,2,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Operators + Vowels Upper Case","+-*/%AEIOUY"} ;
ALPHABET	Alphabet_010			=	{ 10,0,2,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Operators + Vowels Lower Case","+-*/%aeiouy"} ;
ALPHABET	Alphabet_011			=	{ 11,0,3,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Operators + Vowels Lower Case + Vowels Upper Case","+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_012			=	{ 12,0,1,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers","0123456789"} ;
ALPHABET	Alphabet_013			=	{ 13,0,2,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Vowels Upper Case","0123456789AEIOUY"} ;
ALPHABET	Alphabet_014			=	{ 14,0,2,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Vowels Lower Case","0123456789aeiouy"} ;
ALPHABET	Alphabet_015			=	{ 15,0,3,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Vowels Lower Case + Vowels Upper Case","0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_016			=	{ 16,0,2,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Signs","0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_017			=	{ 17,0,3,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Signs + Vowels Upper Case","0123456789 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_018			=	{ 18,0,3,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Signs + Vowels Lower Case","0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_019			=	{ 19,0,4,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Signs + Vowels Lower Case + Vowels Upper Case","0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_020			=	{ 20,0,2,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Operators","0123456789+-*/%"} ;
ALPHABET	Alphabet_021			=	{ 21,0,3,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Operators + Vowels Upper Case","0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_022			=	{ 22,0,3,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Operators + Vowels Lower Case","0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_023			=	{ 23,0,4,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Numbers + Operators + Vowels Lower Case + Vowels Upper Case","0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_024			=	{ 24,0,1,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse","-."} ;
ALPHABET	Alphabet_025			=	{ 25,0,2,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Vowels Upper Case","-.AEIOUY"} ;
ALPHABET	Alphabet_026			=	{ 26,0,2,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Vowels Lower Case","-.aeiouy"} ;
ALPHABET	Alphabet_027			=	{ 27,0,3,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Vowels Lower Case + Vowels Upper Case","-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_028			=	{ 28,0,2,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Operators","-.+-*/%"} ;
ALPHABET	Alphabet_029			=	{ 29,0,3,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Operators + Vowels Upper Case","-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_030			=	{ 30,0,3,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Operators + Vowels Lower Case","-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_031			=	{ 31,0,4,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Operators + Vowels Lower Case + Vowels Upper Case","-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_032			=	{ 32,0,2,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers","-.0123456789"} ;
ALPHABET	Alphabet_033			=	{ 33,0,3,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Vowels Upper Case","-.0123456789AEIOUY"} ;
ALPHABET	Alphabet_034			=	{ 34,0,3,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Vowels Lower Case","-.0123456789aeiouy"} ;
ALPHABET	Alphabet_035			=	{ 35,0,4,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Vowels Lower Case + Vowels Upper Case","-.0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_036			=	{ 36,0,3,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Operators","-.0123456789+-*/%"} ;
ALPHABET	Alphabet_037			=	{ 37,0,4,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Operators + Vowels Upper Case","-.0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_038			=	{ 38,0,4,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Operators + Vowels Lower Case","-.0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_039			=	{ 39,0,5,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Morse + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","-.0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_040			=	{ 40,0,1,szAlphabet_Luc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;
ALPHABET	Alphabet_041			=	{ 41,0,2,szAlphabet_Luc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZaeiouy"} ;
ALPHABET	Alphabet_042			=	{ 42,0,2,szAlphabet_Luc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Signs","ABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_043			=	{ 43,0,3,szAlphabet_Luc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Signs + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_044			=	{ 44,0,2,szAlphabet_Luc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Operators","ABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"} ;
ALPHABET	Alphabet_045			=	{ 45,0,3,szAlphabet_Luc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Operators + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_046			=	{ 46,0,2,szAlphabet_Luc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Numbers","ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"} ;
ALPHABET	Alphabet_047			=	{ 47,0,3,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Numbers + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789aeiouy"} ;
ALPHABET	Alphabet_048			=	{ 48,0,3,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Numbers + Signs","ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_049			=	{ 49,0,4,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Numbers + Signs + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_050			=	{ 50,0,3,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Numbers + Operators","ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/%"} ;
ALPHABET	Alphabet_051			=	{ 51,0,4,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Numbers + Operators + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_052			=	{ 52,0,2,szAlphabet_Luc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse","ABCDEFGHIJKLMNOPQRSTUVWXYZ-."} ;
ALPHABET	Alphabet_053			=	{ 53,0,3,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.aeiouy"} ;
ALPHABET	Alphabet_054			=	{ 54,0,3,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Operators","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%"} ;
ALPHABET	Alphabet_055			=	{ 55,0,4,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Operators + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_056			=	{ 56,0,3,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Numbers","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789"} ;
ALPHABET	Alphabet_057			=	{ 57,0,4,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Numbers + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789aeiouy"} ;
ALPHABET	Alphabet_058			=	{ 58,0,4,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Numbers + Operators","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789+-*/%"} ;
ALPHABET	Alphabet_059			=	{ 59,0,5,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Upper Case + Morse + Numbers + Operators + Vowels Lower Case","ABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_060			=	{ 60,0,1,szAlphabet_Llc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case","abcdefghijklmnopqrstuvwxyz"} ;
ALPHABET	Alphabet_061			=	{ 61,0,2,szAlphabet_Llc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Vowels Upper Case","abcdefghijklmnopqrstuvwxyzAEIOUY"} ;
ALPHABET	Alphabet_062			=	{ 62,0,2,szAlphabet_Llc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Signs","abcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_063			=	{ 63,0,3,szAlphabet_Llc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Signs + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_064			=	{ 64,0,2,szAlphabet_Llc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Operators","abcdefghijklmnopqrstuvwxyz+-*/%"} ;
ALPHABET	Alphabet_065			=	{ 65,0,3,szAlphabet_Llc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Operators + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz+-*/%AEIOUY"} ;
ALPHABET	Alphabet_066			=	{ 66,0,2,szAlphabet_Llc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Numbers","abcdefghijklmnopqrstuvwxyz0123456789"} ;
ALPHABET	Alphabet_067			=	{ 67,0,3,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Numbers + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz0123456789AEIOUY"} ;
ALPHABET	Alphabet_068			=	{ 68,0,3,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Numbers + Signs","abcdefghijklmnopqrstuvwxyz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_069			=	{ 69,0,4,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Numbers + Signs + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_070			=	{ 70,0,3,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Numbers + Operators","abcdefghijklmnopqrstuvwxyz0123456789+-*/%"} ;
ALPHABET	Alphabet_071			=	{ 71,0,4,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Numbers + Operators + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_072			=	{ 72,0,2,szAlphabet_Llc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse","abcdefghijklmnopqrstuvwxyz-."} ;
ALPHABET	Alphabet_073			=	{ 73,0,3,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz-.AEIOUY"} ;
ALPHABET	Alphabet_074			=	{ 74,0,3,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Operators","abcdefghijklmnopqrstuvwxyz-.+-*/%"} ;
ALPHABET	Alphabet_075			=	{ 75,0,4,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Operators + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_076			=	{ 76,0,3,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Numbers","abcdefghijklmnopqrstuvwxyz-.0123456789"} ;
ALPHABET	Alphabet_077			=	{ 77,0,4,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Numbers + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz-.0123456789AEIOUY"} ;
ALPHABET	Alphabet_078			=	{ 78,0,4,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Numbers + Operators","abcdefghijklmnopqrstuvwxyz-.0123456789+-*/%"} ;
ALPHABET	Alphabet_079			=	{ 79,0,5,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Morse + Numbers + Operators + Vowels Upper Case","abcdefghijklmnopqrstuvwxyz-.0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_080			=	{ 80,0,2,szAlphabet_Llc,szAlphabet_Luc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;
ALPHABET	Alphabet_081			=	{ 81,0,3,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Signs","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_082			=	{ 82,0,3,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Operators","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"} ;
ALPHABET	Alphabet_083			=	{ 83,0,3,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Numbers","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"} ;
ALPHABET	Alphabet_084			=	{ 84,0,4,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Numbers + Signs","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_085			=	{ 85,0,4,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Numbers + Operators","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/%"} ;
ALPHABET	Alphabet_086			=	{ 86,0,3,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Morse","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-."} ;
ALPHABET	Alphabet_087			=	{ 87,0,4,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Morse + Operators","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%"} ;
ALPHABET	Alphabet_088			=	{ 88,0,4,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Morse + Numbers","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789"} ;
ALPHABET	Alphabet_089			=	{ 89,0,5,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Letters Lower Case + Letters Upper Case + Morse + Numbers + Operators","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789+-*/%"} ;
ALPHABET	Alphabet_090			=	{ 90,0,1,NULL,szAlphabet_Cuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case","BCDFGHJKLMNPQRSTVWXZ"} ;
ALPHABET	Alphabet_091			=	{ 91,0,2,NULL,szAlphabet_Cuc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZAEIOUY"} ;
ALPHABET	Alphabet_092			=	{ 92,0,2,NULL,szAlphabet_Cuc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZaeiouy"} ;
ALPHABET	Alphabet_093			=	{ 93,0,3,NULL,szAlphabet_Cuc,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZaeiouyAEIOUY"} ;
ALPHABET	Alphabet_094			=	{ 94,0,2,NULL,szAlphabet_Cuc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Signs","BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_095			=	{ 95,0,3,NULL,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Signs + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_096			=	{ 96,0,3,NULL,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Signs + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_097			=	{ 97,0,4,NULL,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Signs + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_098			=	{ 98,0,2,NULL,szAlphabet_Cuc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Operators","BCDFGHJKLMNPQRSTVWXZ+-*/%"} ;
ALPHABET	Alphabet_099			=	{ 99,0,3,NULL,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ+-*/%AEIOUY"} ;
ALPHABET	Alphabet_100			=	{100,0,3,NULL,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Operators + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_101			=	{101,0,4,NULL,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Operators + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_102			=	{102,0,2,NULL,szAlphabet_Cuc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers","BCDFGHJKLMNPQRSTVWXZ0123456789"} ;
ALPHABET	Alphabet_103			=	{103,0,3,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ0123456789AEIOUY"} ;
ALPHABET	Alphabet_104			=	{104,0,3,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ0123456789aeiouy"} ;
ALPHABET	Alphabet_105			=	{105,0,4,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_106			=	{106,0,3,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Signs","BCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_107			=	{107,0,4,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Signs + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_108			=	{108,0,4,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Signs + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_109			=	{109,0,5,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Signs + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_110			=	{110,0,3,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Operators","BCDFGHJKLMNPQRSTVWXZ0123456789+-*/%"} ;
ALPHABET	Alphabet_111			=	{111,0,4,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_112			=	{112,0,4,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Operators + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_113			=	{113,0,5,NULL,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_114			=	{114,0,2,NULL,szAlphabet_Cuc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse","BCDFGHJKLMNPQRSTVWXZ-."} ;
ALPHABET	Alphabet_115			=	{115,0,3,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.AEIOUY"} ;
ALPHABET	Alphabet_116			=	{116,0,3,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ-.aeiouy"} ;
ALPHABET	Alphabet_117			=	{117,0,4,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_118			=	{118,0,3,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Operators","BCDFGHJKLMNPQRSTVWXZ-.+-*/%"} ;
ALPHABET	Alphabet_119			=	{119,0,4,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_120			=	{120,0,4,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Operators + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_121			=	{121,0,5,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Operators + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_122			=	{122,0,3,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers","BCDFGHJKLMNPQRSTVWXZ-.0123456789"} ;
ALPHABET	Alphabet_123			=	{123,0,4,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.0123456789AEIOUY"} ;
ALPHABET	Alphabet_124			=	{124,0,4,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ-.0123456789aeiouy"} ;
ALPHABET	Alphabet_125			=	{125,0,5,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_126			=	{126,0,4,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Operators","BCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%"} ;
ALPHABET	Alphabet_127			=	{127,0,5,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_128			=	{128,0,5,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Operators + Vowels Lower Case","BCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_129			=	{129,0,6,NULL,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Morse + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_130			=	{130,0,2,NULL,szAlphabet_Cuc,szAlphabet_Llc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz"} ;
ALPHABET	Alphabet_131			=	{131,0,3,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyzAEIOUY"} ;
ALPHABET	Alphabet_132			=	{132,0,3,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Signs","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_133			=	{133,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Signs + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_134			=	{134,0,3,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Operators","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz+-*/%"} ;
ALPHABET	Alphabet_135			=	{135,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz+-*/%AEIOUY"} ;
ALPHABET	Alphabet_136			=	{136,0,3,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Numbers","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz0123456789"} ;
ALPHABET	Alphabet_137			=	{137,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Numbers + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz0123456789AEIOUY"} ;
ALPHABET	Alphabet_138			=	{138,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Numbers + Signs","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_139			=	{139,0,5,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Numbers + Signs + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_140			=	{140,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Numbers + Operators","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz0123456789+-*/%"} ;
ALPHABET	Alphabet_141			=	{141,0,5,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Numbers + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_142			=	{142,0,3,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-."} ;
ALPHABET	Alphabet_143			=	{143,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.AEIOUY"} ;
ALPHABET	Alphabet_144			=	{144,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Operators","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.+-*/%"} ;
ALPHABET	Alphabet_145			=	{145,0,5,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_146			=	{146,0,4,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Numbers","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.0123456789"} ;
ALPHABET	Alphabet_147			=	{147,0,5,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Numbers + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.0123456789AEIOUY"} ;
ALPHABET	Alphabet_148			=	{148,0,5,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Numbers + Operators","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.0123456789+-*/%"} ;
ALPHABET	Alphabet_149			=	{149,0,6,NULL,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,"Consonants Upper Case + Letters Lower Case + Morse + Numbers + Operators + Vowels Upper Case","BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_150			=	{150,0,1,szAlphabet_Clc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case","bcdfghjklmnpqrstvwxz"} ;
ALPHABET	Alphabet_151			=	{151,0,2,szAlphabet_Clc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzAEIOUY"} ;
ALPHABET	Alphabet_152			=	{152,0,2,szAlphabet_Clc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Vowels Lower Case","bcdfghjklmnpqrstvwxzaeiouy"} ;
ALPHABET	Alphabet_153			=	{153,0,3,szAlphabet_Clc,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzaeiouyAEIOUY"} ;
ALPHABET	Alphabet_154			=	{154,0,2,szAlphabet_Clc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Signs","bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_155			=	{155,0,3,szAlphabet_Clc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Signs + Vowels Upper Case","bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_156			=	{156,0,3,szAlphabet_Clc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Signs + Vowels Lower Case","bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_157			=	{157,0,4,szAlphabet_Clc,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Signs + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_158			=	{158,0,2,szAlphabet_Clc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Operators","bcdfghjklmnpqrstvwxz+-*/%"} ;
ALPHABET	Alphabet_159			=	{159,0,3,szAlphabet_Clc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxz+-*/%AEIOUY"} ;
ALPHABET	Alphabet_160			=	{160,0,3,szAlphabet_Clc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxz+-*/%aeiouy"} ;
ALPHABET	Alphabet_161			=	{161,0,4,szAlphabet_Clc,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_162			=	{162,0,2,szAlphabet_Clc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers","bcdfghjklmnpqrstvwxz0123456789"} ;
ALPHABET	Alphabet_163			=	{163,0,3,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Vowels Upper Case","bcdfghjklmnpqrstvwxz0123456789AEIOUY"} ;
ALPHABET	Alphabet_164			=	{164,0,3,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Vowels Lower Case","bcdfghjklmnpqrstvwxz0123456789aeiouy"} ;
ALPHABET	Alphabet_165			=	{165,0,4,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_166			=	{166,0,3,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Signs","bcdfghjklmnpqrstvwxz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_167			=	{167,0,4,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Signs + Vowels Upper Case","bcdfghjklmnpqrstvwxz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_168			=	{168,0,4,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Signs + Vowels Lower Case","bcdfghjklmnpqrstvwxz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_169			=	{169,0,5,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Signs + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_170			=	{170,0,3,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Operators","bcdfghjklmnpqrstvwxz0123456789+-*/%"} ;
ALPHABET	Alphabet_171			=	{171,0,4,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxz0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_172			=	{172,0,4,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxz0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_173			=	{173,0,5,szAlphabet_Clc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_174			=	{174,0,2,szAlphabet_Clc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse","bcdfghjklmnpqrstvwxz-."} ;
ALPHABET	Alphabet_175			=	{175,0,3,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.AEIOUY"} ;
ALPHABET	Alphabet_176			=	{176,0,3,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Vowels Lower Case","bcdfghjklmnpqrstvwxz-.aeiouy"} ;
ALPHABET	Alphabet_177			=	{177,0,4,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_178			=	{178,0,3,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Operators","bcdfghjklmnpqrstvwxz-.+-*/%"} ;
ALPHABET	Alphabet_179			=	{179,0,4,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_180			=	{180,0,4,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxz-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_181			=	{181,0,5,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_182			=	{182,0,3,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers","bcdfghjklmnpqrstvwxz-.0123456789"} ;
ALPHABET	Alphabet_183			=	{183,0,4,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.0123456789AEIOUY"} ;
ALPHABET	Alphabet_184			=	{184,0,4,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Vowels Lower Case","bcdfghjklmnpqrstvwxz-.0123456789aeiouy"} ;
ALPHABET	Alphabet_185			=	{185,0,5,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_186			=	{186,0,4,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Operators","bcdfghjklmnpqrstvwxz-.0123456789+-*/%"} ;
ALPHABET	Alphabet_187			=	{187,0,5,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_188			=	{188,0,5,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxz-.0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_189			=	{189,0,6,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Morse + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxz-.0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_190			=	{190,0,2,szAlphabet_Clc,szAlphabet_Luc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;
ALPHABET	Alphabet_191			=	{191,0,3,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZaeiouy"} ;
ALPHABET	Alphabet_192			=	{192,0,3,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Signs","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_193			=	{193,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Signs + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_194			=	{194,0,3,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Operators","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"} ;
ALPHABET	Alphabet_195			=	{195,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_196			=	{196,0,3,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Numbers","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"} ;
ALPHABET	Alphabet_197			=	{197,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Numbers + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789aeiouy"} ;
ALPHABET	Alphabet_198			=	{198,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Numbers + Signs","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_199			=	{199,0,5,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Numbers + Signs + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_200			=	{200,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Numbers + Operators","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/%"} ;
ALPHABET	Alphabet_201			=	{201,0,5,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Numbers + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_202			=	{202,0,3,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-."} ;
ALPHABET	Alphabet_203			=	{203,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.aeiouy"} ;
ALPHABET	Alphabet_204			=	{204,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Operators","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%"} ;
ALPHABET	Alphabet_205			=	{205,0,5,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_206			=	{206,0,4,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Numbers","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789"} ;
ALPHABET	Alphabet_207			=	{207,0,5,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Numbers + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789aeiouy"} ;
ALPHABET	Alphabet_208			=	{208,0,5,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Numbers + Operators","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789+-*/%"} ;
ALPHABET	Alphabet_209			=	{209,0,6,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Letters Upper Case + Morse + Numbers + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_210			=	{210,0,2,szAlphabet_Clc,szAlphabet_Cuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ"} ;
ALPHABET	Alphabet_211			=	{211,0,3,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZAEIOUY"} ;
ALPHABET	Alphabet_212			=	{212,0,3,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZaeiouy"} ;
ALPHABET	Alphabet_213			=	{213,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZaeiouyAEIOUY"} ;
ALPHABET	Alphabet_214			=	{214,0,3,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Signs","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_215			=	{215,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Signs + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_216			=	{216,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Signs + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_217			=	{217,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Signs + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_218			=	{218,0,3,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Operators","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%"} ;
ALPHABET	Alphabet_219			=	{219,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%AEIOUY"} ;
ALPHABET	Alphabet_220			=	{220,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_221			=	{221,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_222			=	{222,0,3,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789"} ;
ALPHABET	Alphabet_223			=	{223,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789AEIOUY"} ;
ALPHABET	Alphabet_224			=	{224,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789aeiouy"} ;
ALPHABET	Alphabet_225			=	{225,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_226			=	{226,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Signs","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_227			=	{227,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Signs + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_228			=	{228,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Signs + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_229			=	{229,0,6,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Signs + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789 !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_230			=	{230,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Operators","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789+-*/%"} ;
ALPHABET	Alphabet_231			=	{231,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_232			=	{232,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_233			=	{233,0,6,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_234			=	{234,0,3,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-."} ;
ALPHABET	Alphabet_235			=	{235,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.AEIOUY"} ;
ALPHABET	Alphabet_236			=	{236,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.aeiouy"} ;
ALPHABET	Alphabet_237			=	{237,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_238			=	{238,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Operators","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%"} ;
ALPHABET	Alphabet_239			=	{239,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_240			=	{240,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_241			=	{241,0,6,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_242			=	{242,0,4,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789"} ;
ALPHABET	Alphabet_243			=	{243,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789AEIOUY"} ;
ALPHABET	Alphabet_244			=	{244,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789aeiouy"} ;
ALPHABET	Alphabet_245			=	{245,0,6,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789aeiouyAEIOUY"} ;
ALPHABET	Alphabet_246			=	{246,0,5,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Operators","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%"} ;
ALPHABET	Alphabet_247			=	{247,0,6,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Operators + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%AEIOUY"} ;
ALPHABET	Alphabet_248			=	{248,0,6,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Operators + Vowels Lower Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%aeiouy"} ;
ALPHABET	Alphabet_249			=	{249,0,7,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Numbers,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,"Consonants Lower Case + Consonants Upper Case + Morse + Numbers + Operators + Vowels Lower Case + Vowels Upper Case","bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.0123456789+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_250			=	{250,0,1,szAlphabet_Binary,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary","01"} ;
ALPHABET	Alphabet_251			=	{251,0,2,szAlphabet_Binary,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Vowels Upper Case","01AEIOUY"} ;
ALPHABET	Alphabet_252			=	{252,0,2,szAlphabet_Binary,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Vowels Lower Case","01aeiouy"} ;
ALPHABET	Alphabet_253			=	{253,0,3,szAlphabet_Binary,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Vowels Lower Case + Vowels Upper Case","01aeiouyAEIOUY"} ;
ALPHABET	Alphabet_254			=	{254,0,2,szAlphabet_Binary,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Signs","01 !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_255			=	{255,0,3,szAlphabet_Binary,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Signs + Vowels Upper Case","01 !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_256			=	{256,0,3,szAlphabet_Binary,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Signs + Vowels Lower Case","01 !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_257			=	{257,0,4,szAlphabet_Binary,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Signs + Vowels Lower Case + Vowels Upper Case","01 !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_258			=	{258,0,2,szAlphabet_Binary,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Operators","01+-*/%"} ;
ALPHABET	Alphabet_259			=	{259,0,3,szAlphabet_Binary,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Operators + Vowels Upper Case","01+-*/%AEIOUY"} ;
ALPHABET	Alphabet_260			=	{260,0,3,szAlphabet_Binary,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Operators + Vowels Lower Case","01+-*/%aeiouy"} ;
ALPHABET	Alphabet_261			=	{261,0,4,szAlphabet_Binary,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Operators + Vowels Lower Case + Vowels Upper Case","01+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_262			=	{262,0,2,szAlphabet_Binary,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse","01-."} ;
ALPHABET	Alphabet_263			=	{263,0,3,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Vowels Upper Case","01-.AEIOUY"} ;
ALPHABET	Alphabet_264			=	{264,0,3,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Vowels Lower Case","01-.aeiouy"} ;
ALPHABET	Alphabet_265			=	{265,0,4,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Vowels Lower Case + Vowels Upper Case","01-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_266			=	{266,0,3,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Operators","01-.+-*/%"} ;
ALPHABET	Alphabet_267			=	{267,0,4,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Operators + Vowels Upper Case","01-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_268			=	{268,0,4,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Operators + Vowels Lower Case","01-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_269			=	{269,0,5,szAlphabet_Binary,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Morse + Operators + Vowels Lower Case + Vowels Upper Case","01-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_270			=	{270,0,2,szAlphabet_Binary,szAlphabet_Luc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case","01ABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;
ALPHABET	Alphabet_271			=	{271,0,3,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Vowels Lower Case","01ABCDEFGHIJKLMNOPQRSTUVWXYZaeiouy"} ;
ALPHABET	Alphabet_272			=	{272,0,3,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Signs","01ABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_273			=	{273,0,4,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Signs + Vowels Lower Case","01ABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_274			=	{274,0,3,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Operators","01ABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"} ;
ALPHABET	Alphabet_275			=	{275,0,4,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Operators + Vowels Lower Case","01ABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_276			=	{276,0,3,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Morse","01ABCDEFGHIJKLMNOPQRSTUVWXYZ-."} ;
ALPHABET	Alphabet_277			=	{277,0,4,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Morse + Vowels Lower Case","01ABCDEFGHIJKLMNOPQRSTUVWXYZ-.aeiouy"} ;
ALPHABET	Alphabet_278			=	{278,0,4,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Morse + Operators","01ABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%"} ;
ALPHABET	Alphabet_279			=	{279,0,5,szAlphabet_Binary,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Upper Case + Morse + Operators + Vowels Lower Case","01ABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_280			=	{280,0,2,szAlphabet_Binary,szAlphabet_Llc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case","01abcdefghijklmnopqrstuvwxyz"} ;
ALPHABET	Alphabet_281			=	{281,0,3,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Vowels Upper Case","01abcdefghijklmnopqrstuvwxyzAEIOUY"} ;
ALPHABET	Alphabet_282			=	{282,0,3,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Signs","01abcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_283			=	{283,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Signs + Vowels Upper Case","01abcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_284			=	{284,0,3,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Operators","01abcdefghijklmnopqrstuvwxyz+-*/%"} ;
ALPHABET	Alphabet_285			=	{285,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Operators + Vowels Upper Case","01abcdefghijklmnopqrstuvwxyz+-*/%AEIOUY"} ;
ALPHABET	Alphabet_286			=	{286,0,3,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Morse","01abcdefghijklmnopqrstuvwxyz-."} ;
ALPHABET	Alphabet_287			=	{287,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Morse + Vowels Upper Case","01abcdefghijklmnopqrstuvwxyz-.AEIOUY"} ;
ALPHABET	Alphabet_288			=	{288,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Morse + Operators","01abcdefghijklmnopqrstuvwxyz-.+-*/%"} ;
ALPHABET	Alphabet_289			=	{289,0,5,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Morse + Operators + Vowels Upper Case","01abcdefghijklmnopqrstuvwxyz-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_290			=	{290,0,3,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Luc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Letters Upper Case","01abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;
ALPHABET	Alphabet_291			=	{291,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Letters Upper Case + Signs","01abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_292			=	{292,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Letters Upper Case + Operators","01abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"} ;
ALPHABET	Alphabet_293			=	{293,0,4,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Letters Upper Case + Morse","01abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-."} ;
ALPHABET	Alphabet_294			=	{294,0,5,szAlphabet_Binary,szAlphabet_Llc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Letters Lower Case + Letters Upper Case + Morse + Operators","01abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%"} ;
ALPHABET	Alphabet_295			=	{295,0,2,szAlphabet_Binary,szAlphabet_Cuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case","01BCDFGHJKLMNPQRSTVWXZ"} ;
ALPHABET	Alphabet_296			=	{296,0,3,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZAEIOUY"} ;
ALPHABET	Alphabet_297			=	{297,0,3,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Vowels Lower Case","01BCDFGHJKLMNPQRSTVWXZaeiouy"} ;
ALPHABET	Alphabet_298			=	{298,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Vowels Lower Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZaeiouyAEIOUY"} ;
ALPHABET	Alphabet_299			=	{299,0,3,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Signs","01BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_300			=	{300,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Signs + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_301			=	{301,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Signs + Vowels Lower Case","01BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_302			=	{302,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Signs + Vowels Lower Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_303			=	{303,0,3,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Operators","01BCDFGHJKLMNPQRSTVWXZ+-*/%"} ;
ALPHABET	Alphabet_304			=	{304,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Operators + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ+-*/%AEIOUY"} ;
ALPHABET	Alphabet_305			=	{305,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Operators + Vowels Lower Case","01BCDFGHJKLMNPQRSTVWXZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_306			=	{306,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Operators + Vowels Lower Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_307			=	{307,0,3,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse","01BCDFGHJKLMNPQRSTVWXZ-."} ;
ALPHABET	Alphabet_308			=	{308,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ-.AEIOUY"} ;
ALPHABET	Alphabet_309			=	{309,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Vowels Lower Case","01BCDFGHJKLMNPQRSTVWXZ-.aeiouy"} ;
ALPHABET	Alphabet_310			=	{310,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Vowels Lower Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_311			=	{311,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Operators","01BCDFGHJKLMNPQRSTVWXZ-.+-*/%"} ;
ALPHABET	Alphabet_312			=	{312,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Operators + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_313			=	{313,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Operators + Vowels Lower Case","01BCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_314			=	{314,0,6,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Morse + Operators + Vowels Lower Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_315			=	{315,0,3,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz"} ;
ALPHABET	Alphabet_316			=	{316,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyzAEIOUY"} ;
ALPHABET	Alphabet_317			=	{317,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Signs","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_318			=	{318,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Signs + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_319			=	{319,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Operators","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz+-*/%"} ;
ALPHABET	Alphabet_320			=	{320,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Operators + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz+-*/%AEIOUY"} ;
ALPHABET	Alphabet_321			=	{321,0,4,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Morse","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-."} ;
ALPHABET	Alphabet_322			=	{322,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Morse + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.AEIOUY"} ;
ALPHABET	Alphabet_323			=	{323,0,5,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Morse + Operators","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.+-*/%"} ;
ALPHABET	Alphabet_324			=	{324,0,6,szAlphabet_Binary,szAlphabet_Cuc,szAlphabet_Llc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Upper Case + Letters Lower Case + Morse + Operators + Vowels Upper Case","01BCDFGHJKLMNPQRSTVWXZabcdefghijklmnopqrstuvwxyz-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_325			=	{325,0,2,szAlphabet_Binary,szAlphabet_Clc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case","01bcdfghjklmnpqrstvwxz"} ;
ALPHABET	Alphabet_326			=	{326,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzAEIOUY"} ;
ALPHABET	Alphabet_327			=	{327,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Vowels Lower Case","01bcdfghjklmnpqrstvwxzaeiouy"} ;
ALPHABET	Alphabet_328			=	{328,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzaeiouyAEIOUY"} ;
ALPHABET	Alphabet_329			=	{329,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Signs","01bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_330			=	{330,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Signs + Vowels Upper Case","01bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_331			=	{331,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Signs + Vowels Lower Case","01bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_332			=	{332,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Signs + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxz !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_333			=	{333,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Operators","01bcdfghjklmnpqrstvwxz+-*/%"} ;
ALPHABET	Alphabet_334			=	{334,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Operators + Vowels Upper Case","01bcdfghjklmnpqrstvwxz+-*/%AEIOUY"} ;
ALPHABET	Alphabet_335			=	{335,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Operators + Vowels Lower Case","01bcdfghjklmnpqrstvwxz+-*/%aeiouy"} ;
ALPHABET	Alphabet_336			=	{336,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Operators + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxz+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_337			=	{337,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse","01bcdfghjklmnpqrstvwxz-."} ;
ALPHABET	Alphabet_338			=	{338,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Vowels Upper Case","01bcdfghjklmnpqrstvwxz-.AEIOUY"} ;
ALPHABET	Alphabet_339			=	{339,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Vowels Lower Case","01bcdfghjklmnpqrstvwxz-.aeiouy"} ;
ALPHABET	Alphabet_340			=	{340,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxz-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_341			=	{341,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Operators","01bcdfghjklmnpqrstvwxz-.+-*/%"} ;
ALPHABET	Alphabet_342			=	{342,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Operators + Vowels Upper Case","01bcdfghjklmnpqrstvwxz-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_343			=	{343,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Operators + Vowels Lower Case","01bcdfghjklmnpqrstvwxz-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_344			=	{344,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Morse + Operators + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxz-.+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_345			=	{345,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ"} ;
ALPHABET	Alphabet_346			=	{346,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Vowels Lower Case","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZaeiouy"} ;
ALPHABET	Alphabet_347			=	{347,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Signs","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_348			=	{348,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Signs + Vowels Lower Case","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_349			=	{349,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Operators","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%"} ;
ALPHABET	Alphabet_350			=	{350,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Operators + Vowels Lower Case","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_351			=	{351,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Morse","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-."} ;
ALPHABET	Alphabet_352			=	{352,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Morse + Vowels Lower Case","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.aeiouy"} ;
ALPHABET	Alphabet_353			=	{353,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Morse + Operators","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%"} ;
ALPHABET	Alphabet_354			=	{354,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Luc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Letters Upper Case + Morse + Operators + Vowels Lower Case","01bcdfghjklmnpqrstvwxzABCDEFGHIJKLMNOPQRSTUVWXYZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_355			=	{355,0,3,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ"} ;
ALPHABET	Alphabet_356			=	{356,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZAEIOUY"} ;
ALPHABET	Alphabet_357			=	{357,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Vowels Lower Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZaeiouy"} ;
ALPHABET	Alphabet_358			=	{358,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZaeiouyAEIOUY"} ;
ALPHABET	Alphabet_359			=	{359,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Signs","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}"} ;
ALPHABET	Alphabet_360			=	{360,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Signs + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}AEIOUY"} ;
ALPHABET	Alphabet_361			=	{361,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Signs + Vowels Lower Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouy"} ;
ALPHABET	Alphabet_362			=	{362,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Signs,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Signs + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ !\\\"#$%&'(),:;<=>?@[]_{}aeiouyAEIOUY"} ;
ALPHABET	Alphabet_363			=	{363,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Operators","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%"} ;
ALPHABET	Alphabet_364			=	{364,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Operators + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%AEIOUY"} ;
ALPHABET	Alphabet_365			=	{365,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Operators + Vowels Lower Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%aeiouy"} ;
ALPHABET	Alphabet_366			=	{366,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Operators + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ+-*/%aeiouyAEIOUY"} ;
ALPHABET	Alphabet_367			=	{367,0,4,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-."} ;
ALPHABET	Alphabet_368			=	{368,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.AEIOUY"} ;
ALPHABET	Alphabet_369			=	{369,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Vowels Lower Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.aeiouy"} ;
ALPHABET	Alphabet_370			=	{370,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.aeiouyAEIOUY"} ;
ALPHABET	Alphabet_371			=	{371,0,5,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Operators","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%"} ;
ALPHABET	Alphabet_372			=	{372,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Operators + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%AEIOUY"} ;
ALPHABET	Alphabet_373			=	{373,0,6,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,NULL,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Operators + Vowels Lower Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouy"} ;
ALPHABET	Alphabet_374			=	{374,0,7,szAlphabet_Binary,szAlphabet_Clc,szAlphabet_Cuc,szAlphabet_Morse,szAlphabet_Operators,szAlphabet_Vlc,szAlphabet_Vuc,NULL,NULL,NULL,NULL,NULL,"Binary + Consonants Lower Case + Consonants Upper Case + Morse + Operators + Vowels Lower Case + Vowels Upper Case","01bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ-.+-*/%aeiouyAEIOUY"} ;

static char szAbacus_128[]		=	"Abacus (128 bits)" ;
static char szAbacus_160[]		=	"Abacus (160 bits)" ;
static char szAbacus_192[]		=	"Abacus (192 bits)" ;
static char szAbacus_224[]		=	"Abacus (224 bits)" ;
static char szAbacus_256[]		=	"Abacus (256 bits)" ;
static char szAbacus_384[]		=	"Abacus (384 bits)" ;
static char szAbacus_512[]		=	"Abacus (512 bits)" ;
static char szAbacus_1024[]		=	"Abacus (1024 bits)" ;
static char szAriRang_224[]		=	"AriRang (224 bits)" ;
static char szAriRang_256[]		=	"AriRang (256 bits)" ;
static char szAriRang_384[]		=	"AriRang (384 bits)" ;
static char szAriRang_512[]		=	"AriRang (512 bits)" ;
static char szAurora_224[]		=	"Aurora (224 bits)" ;
static char szAurora_256[]		=	"Aurora (256 bits)" ;
static char szAurora_384[]		=	"Aurora (384 bits)" ;
static char szAurora_512[]		=	"Aurora (512 bits)" ;
static char szBlake_224[]		=	"Blake (224 bits)" ;
static char szBlake_256[]		=	"Blake (256 bits)" ;
static char szBlake_384[]		=	"Blake (384 bits)" ;
static char szBlake_512[]		=	"Blake (512 bits)" ;
static char szBlender_192[]		=	"Blender (192 bits)" ;
static char szBlender_224[]		=	"Blender (224 bits)" ;
static char szBlender_256[]		=	"Blender (256 bits)" ;
static char szBlender_288[]		=	"Blender (288 bits)" ;
static char szBlender_320[]		=	"Blender (320 bits)" ;
static char szBlender_384[]		=	"Blender (384 bits)" ;
static char szBlender_448[]		=	"Blender (448 bits)" ;
static char szBlender_512[]		=	"Blender (512 bits)" ;
static char szBlender_576[]		=	"Blender (576 bits)" ;
static char szBlender_640[]		=	"Blender (640 bits)" ;
static char szBmw_224[]			=	"Bmw (224 bits)" ;
static char szBmw_256[]			=	"Bmw (256 bits)" ;
static char szBmw_384[]			=	"Bmw (384 bits)" ;
static char szBmw_512[]			=	"Bmw (512 bits)" ;
static char szCheetah_224[]		=	"Cheetah (224 bits)" ;
static char szCheetah_256[]		=	"Cheetah (256 bits)" ;
static char szCheetah_384[]		=	"Cheetah (384 bits)" ;
static char szCheetah_512[]		=	"Cheetah (512 bits)" ;
static char szCrunch_224[]		=	"Crunch (224 bits)" ;
static char szCrunch_256[]		=	"Crunch (256 bits)" ;
static char szCrunch_384[]		=	"Crunch (384 bits)" ;
static char szCrunch_512[]		=	"Crunch (512 bits)" ;
static char szCubeHash_224[]	=	"CubeHash (224 bits)" ;
static char szCubeHash_256[]	=	"CubeHash (256 bits)" ;
static char szCubeHash_384[]	=	"CubeHash (384 bits)" ;
static char szCubeHash_512[]	=	"CubeHash (512 bits)" ;
static char szEcho_224[]		=	"Echo (224 bits)" ;
static char szEcho_256[]		=	"Echo (256 bits)" ;
static char szEcho_384[]		=	"Echo (384 bits)" ;
static char szEcho_512[]		=	"Echo (512 bits)" ;
static char szFugue_224[]		=	"Fugue (224 bits)" ;
static char szFugue_256[]		=	"Fugue (256 bits)" ;
static char szFugue_384[]		=	"Fugue (384 bits)" ;
static char szFugue_512[]		=	"Fugue (512 bits)" ;
static char szGrostl_224[]		=	"GrÃ¸stl (224 bits)" ;
static char szGrostl_256[]		=	"Grostl (256 bits)" ;
static char szGrostl_384[]		=	"Grostl (384 bits)" ;
static char szGrostl_512[]		=	"Grostl (512 bits)" ;
static char szHamsi_224[]		=	"Hamsi (224 bits)" ;
static char szHamsi_256[]		=	"Hamsi (256 bits)" ;
static char szHamsi_384[]		=	"Hamsi (384 bits)" ;
static char szHamsi_512[]		=	"Hamsi (512 bits)" ;
static char szHaval_3_128[]		=	"Haval_3 (128 bits)" ;
static char szHaval_3_160[]		=	"Haval_3 (160 bits)" ;
static char szHaval_3_192[]		=	"Haval_3 (192 bits)" ;
static char szHaval_3_224[]		=	"Haval_3 (224 bits)" ;
static char szHaval_3_256[]		=	"Haval_3 (256 bits)" ;
static char szHaval_4_128[]		=	"Haval_4 (128 bits)" ;
static char szHaval_4_160[]		=	"Haval_4 (160 bits)" ;
static char szHaval_4_192[]		=	"Haval_4 (192 bits)" ;
static char szHaval_4_224[]		=	"Haval_4 (224 bits)" ;
static char szHaval_4_256[]		=	"Haval_4 (256 bits)" ;
static char szHaval_5_128[]		=	"Haval_5 (128 bits)" ;
static char szHaval_5_160[]		=	"Haval_5 (160 bits)" ;
static char szHaval_5_192[]		=	"Haval_5 (192 bits)" ;
static char szHaval_5_224[]		=	"Haval_5 (224 bits)" ;
static char szHaval_5_256[]		=	"Haval_5 (256 bits)" ;
static char szJh_224[]			=	"Jh (224 bits)" ;
static char szJh_256[]			=	"Jh (256 bits)" ;
static char szJh_384[]			=	"Jh (384 bits)" ;
static char szJh_512[]			=	"Jh (512 bits)" ;
static char szKeccak_224[]		=	"Keccak / Sha 3 (224 bits)" ;
static char szKeccak_256[]		=	"Keccak / Sha 3 (256 bits)" ;
static char szKeccak_384[]		=	"Keccak / Sha 3 (384 bits)" ;
static char szKeccak_512[]		=	"Keccak / Sha 3 (512 bits)" ;
static char szLuffa_224[]		=	"Luffa (224 bits)" ;
static char szLuffa_256[]		=	"Luffa (256 bits)" ;
static char szLuffa_384[]		=	"Luffa (384 bits)" ;
static char szLuffa_512[]		=	"Luffa (512 bits)" ;
static char szMaraca_128[]		=	"Maraca (128 bits)" ;
static char szMd_2_128[]		=	"Md 2 (128 bits)" ;
static char szMd_4_128[]		=	"Md 4 (128 bits)" ;
static char szMd_5_128[]		=	"Md 5 (128 bits)" ;
static char szMd5Md5_A_128[]	=	"HMAC / MD5(MD5(A)) (128 bits)" ;
static char szMd_5_Sha1_A_128[]	=	"Md 5(Sha1) / MD5(SHA1(A)) (128 bits)" ;
static char szMd5Md5_N_128[]	=	"HMAC / MD5(MD5(N)) (128 bits)" ;
static char szMd_5_Sha1_N_128[]	=	"Md 5(Sha1) / MD5(SHA1(N)) (128 bits)" ;
static char szMd_6_128[]		=	"Md 6 (128 bits)" ;
static char szMd_6_160[]		=	"Md 6 (160 bits)" ;
static char szMd_6_192[]		=	"Md 6 (192 bits)" ;
static char szMd_6_224[]		=	"Md 6 (224 bits)" ;
static char szMd_6_256[]		=	"Md 6 (256 bits)" ;
static char szMd_6_384[]		=	"Md 6 (384 bits)" ;
static char szMd_6_512[]		=	"Md 6 (512 bits)" ;
static char szPanama_256[]		=	"Panama (256 bits)" ;
static char szRadioGatun_256[]	=	"RadioGatun (256 bits)" ;
static char szRadioGatun_64[]	=	"RadioGatun (64 bits)" ;
static char szRipeMd_128[]		=	"RipeMd (128 bits)" ;
static char szRipeMd_160[]		=	"RipeMd (160 bits)" ;
static char szSarmal_224[]		=	"Sarmal (224 bits)" ;
static char szSarmal_256[]		=	"Sarmal (256 bits)" ;
static char szSarmal_384[]		=	"Sarmal (384 bits)" ;
static char szSarmal_512[]		=	"Sarmal (512 bits)" ;
static char szSha_0_160[]		=	"Sha 0 (160 bits)" ;
static char szSha_1_160[]		=	"Sha 1 (160 bits)" ;
static char szSha_1_Md5_A_160[]	=	"Sha 1(Md 5) / SHA1(MD5(A)) (160 bits)" ;
static char szSha_1_Sha1_A_160[]=	"Sha 1(Sha1) / SHA1(SHA1(A)) / (160 bits)" ;
static char szSha_1_Md5_N_160[]	=	"Sha 1(Md 5) / SHA1(MD5(N)) (160 bits)" ;
static char szSha_1_Sha1_N_160[]=	"Sha 1(Sha1) / SHA1(SHA1(N)) / (160 bits)" ;
static char szSha_2_224[]		=	"Sha 2 (224 bits)" ;
static char szSha_2_256[]		=	"Sha 2 (256 bits)" ;
static char szSha_2_384[]		=	"Sha 2 (384 bits)" ;
static char szSha_2_512[]		=	"Sha 2 (512 bits)" ;
static char szShabal_192[]		=	"Shabal (192 bits)" ;
static char szShabal_224[]		=	"Shabal (224 bits)" ;
static char szShabal_256[]		=	"Shabal (256 bits)" ;
static char szShabal_384[]		=	"Shabal (384 bits)" ;
static char szShabal_512[]		=	"Shabal (512 bits)" ;
static char szShavite_224[]		=	"Shavite (224 bits)" ;
static char szShavite_256[]		=	"Shavite (256 bits)" ;
static char szShavite_384[]		=	"Shavite (384 bits)" ;
static char szShavite_512[]		=	"Shavite (512 bits)" ;
static char szSkein_224[]		=	"Skein (224 bits)" ;
static char szSkein_256[]		=	"Skein (256 bits)" ;
static char szSkein_384[]		=	"Skein (384 bits)" ;
static char szSkein_512[]		=	"Skein (512 bits)" ;
static char szStreamHash_224[]	=	"Stream Hash (224 bits)" ;
static char szStreamHash_256[]	=	"Stream Hash (256 bits)" ;
static char szStreamHash_384[]	=	"Stream Hash (384 bits)" ;
static char szStreamHash_512[]	=	"Stream Hash (512 bits)" ;
static char szTiger_192[]		=	"Tiger (192 bits)" ;
static char szWaterfall_512[]	=	"Waterfall (512 bits)" ;
static char szWhirlpool_512[]	=	"Whirlpool (512 bits)" ;

char	szFmt_Select[]					=	"SELECT [Length] FROM [Hashes] WHERE [Password] LIKE \"%w\"" ;

char	szGeneratePasswords[]			=	"Password Finder - Generate passwords" ;
char	szRunning[]						=	"...Running..." ;
char	szFinished[]					=	"...Finished..." ;
char	szWaiting[]						=	"...Waiting..." ;
char	szSuccess[]						=	"...Success..." ;
char	szFailure[]						=	"...Failure..." ;
char	szTooShort[]					=	"...Too Short..." ;
char	szEmptyString[]					=	"...Empty String..." ;
char	szError[]						=	"...Error..." ;
char	szReady[]						=	"...Ready..." ;
char	szPleaseWait[]					=	"...Please wait..." ;
char	szVacuum[]						=	"...Vacuum..." ;
char	szSQLiteVacuum[]				=	"Vacuum" ;
char	szDatabases[]					=	"Databases" ;
char	szSetThreadPriority[]			=	"SetThreadPriority" ;
char	szBeginTransaction[]			=	"BEGIN EXCLUSIVE TRANSACTION" ;
char	szEndTransaction[]				=	"END TRANSACTION" ;
char	szFmt_Tbl_Round_Algo[]			=	"%s\\%3.3d_%3.3d_%3.3d_%4.4d (R %lu).db3" ;
char	szTbl_Fmt_Insert[]				=	"INSERT INTO Hashes([Password],[Hash]) VALUES (\"%w\",\"%s\")" ;
char	szTbl_Fmt_Results_Insert[]		=	"INSERT INTO Results([RecordNumber],[Length],[HashSize],[Password],[Hash],[FileName]) "
											"VALUES (%lu,%lu,%lu,\"%w\",\"%s\",\"%s\")" ;
char	szFmt_Tbl_Create[]				=	"CREATE TABLE [Hashes] (\n"
											"[Password] CHAR(256) COLLATE BINARY,\n"
											"[Hash] CHAR(128) COLLATE BINARY,\n"
											"CONSTRAINT [Cnstr] PRIMARY KEY([Password] COLLATE [BINARY] ASC, [Hash] COLLATE [BINARY] ASC) ON CONFLICT ABORT) ;\n" ;
char	szResult_Create[]				=	"CREATE TABLE [Results] (\n"
											"[RecordNumber] INTEGER NOT NULL ON CONFLICT ABORT COLLATE BINARY DEFAULT 0,\n"
											"[Length] INTEGER COLLATE BINARY DEFAULT 0,\n"
											"[HashSize] INTEGER COLLATE BINARY DEFAULT 0,\n"
											"[Password] CHAR(256) COLLATE BINARY DEFAULT \"-\",\n"
											"[Hash] CHAR(256) COLLATE BINARY DEFAULT \"-\",\n"
											"[FileName] CHAR(260) COLLATE BINARY DEFAULT \"-\",\n"
											"CONSTRAINT [Idx_Result] PRIMARY KEY ([RecordNumber] COLLATE BINARY ASC) ON CONFLICT FAIL) WITHOUT ROWID ;\n" ;

DB_INFOS	Db_Abacus_128		=	{  1,szAbacus_128,			HASH_BYTES_128,	HASH_BITS_128,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_160		=	{  2,szAbacus_160,			HASH_BYTES_160,	HASH_BITS_160,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_192		=	{  3,szAbacus_192,			HASH_BYTES_192,	HASH_BITS_192,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_224		=	{  4,szAbacus_224,			HASH_BYTES_224,	HASH_BITS_224,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_256		=	{  5,szAbacus_256,			HASH_BYTES_256,	HASH_BITS_256,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_384		=	{  6,szAbacus_384,			HASH_BYTES_384,	HASH_BITS_384,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_512		=	{  7,szAbacus_512,			HASH_BYTES_512,	HASH_BITS_512,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Abacus_1024		=	{  8,szAbacus_1024,			HASH_BYTES_1024,HASH_BITS_1024,	Abacus_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_AriRang_224		=	{  9,szAriRang_224,			HASH_BYTES_224,	HASH_BITS_224,	AriRang_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_AriRang_256		=	{ 10,szAriRang_256,			HASH_BYTES_256,	HASH_BITS_256,	AriRang_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_AriRang_384		=	{ 11,szAriRang_384,			HASH_BYTES_384,	HASH_BITS_384,	AriRang_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_AriRang_512		=	{ 12,szAriRang_512,			HASH_BYTES_512,	HASH_BITS_512,	AriRang_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Aurora_224		=	{ 13,szAurora_224,			HASH_BYTES_224,	HASH_BITS_224,	Aurora_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Aurora_256		=	{ 14,szAurora_256,			HASH_BYTES_256,	HASH_BITS_256,	Aurora_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Aurora_384		=	{ 15,szAurora_384,			HASH_BYTES_384,	HASH_BITS_384,	Aurora_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Aurora_512		=	{ 16,szAurora_512,			HASH_BYTES_512,	HASH_BITS_512,	Aurora_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blake_224		=	{ 17,szBlake_224,			HASH_BYTES_224,	HASH_BITS_224,	Blake_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blake_256		=	{ 18,szBlake_256,			HASH_BYTES_256,	HASH_BITS_256,	Blake_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blake_384		=	{ 19,szBlake_384,			HASH_BYTES_384,	HASH_BITS_384,	Blake_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blake_512		=	{ 20,szBlake_512,			HASH_BYTES_512,	HASH_BITS_512,	Blake_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_192		=	{ 21,szBlender_192,			HASH_BYTES_192,	HASH_BITS_224,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_224		=	{ 22,szBlender_224,			HASH_BYTES_224,	HASH_BITS_224,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_256		=	{ 23,szBlender_256,			HASH_BYTES_256,	HASH_BITS_256,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_288		=	{ 24,szBlender_288,			HASH_BYTES_288,	HASH_BITS_288,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_320		=	{ 25,szBlender_320,			HASH_BYTES_320,	HASH_BITS_320,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_384		=	{ 26,szBlender_384,			HASH_BYTES_384,	HASH_BITS_384,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_448		=	{ 27,szBlender_448,			HASH_BYTES_448,	HASH_BITS_448,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_512		=	{ 28,szBlender_512,			HASH_BYTES_512,	HASH_BITS_512,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_576		=	{ 29,szBlender_576,			HASH_BYTES_576,	HASH_BITS_576,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Blender_640		=	{ 30,szBlender_640,			HASH_BYTES_640,	HASH_BITS_640,	Blender_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Bmw_224			=	{ 31,szBmw_224,				HASH_BYTES_224,	HASH_BITS_224,	Bmw_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Bmw_256			=	{ 32,szBmw_256,				HASH_BYTES_256,	HASH_BITS_256,	Bmw_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Bmw_384			=	{ 33,szBmw_384,				HASH_BYTES_384,	HASH_BITS_384,	Bmw_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Bmw_512			=	{ 34,szBmw_512,				HASH_BYTES_512,	HASH_BITS_512,	Bmw_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Cheetah_224		=	{ 35,szCheetah_224,			HASH_BYTES_224,	HASH_BITS_224,	Cheetah_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Cheetah_256		=	{ 36,szCheetah_256,			HASH_BYTES_256,	HASH_BITS_256,	Cheetah_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Cheetah_384		=	{ 37,szCheetah_384,			HASH_BYTES_384,	HASH_BITS_384,	Cheetah_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Cheetah_512		=	{ 38,szCheetah_512,			HASH_BYTES_512,	HASH_BITS_512,	Cheetah_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Crunch_224		=	{ 39,szCrunch_224,			HASH_BYTES_224,	HASH_BITS_224,	Crunch_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Crunch_256		=	{ 40,szCrunch_256,			HASH_BYTES_256,	HASH_BITS_256,	Crunch_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Crunch_384		=	{ 41,szCrunch_384,			HASH_BYTES_384,	HASH_BITS_384,	Crunch_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Crunch_512		=	{ 42,szCrunch_512,			HASH_BYTES_512,	HASH_BITS_512,	Crunch_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_CubeHash_224		=	{ 43,szCubeHash_224,		HASH_BYTES_224,	HASH_BITS_224,	CubeHash_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_CubeHash_256		=	{ 44,szCubeHash_256,		HASH_BYTES_256,	HASH_BITS_256,	CubeHash_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_CubeHash_384		=	{ 45,szCubeHash_384,		HASH_BYTES_384,	HASH_BITS_384,	CubeHash_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_CubeHash_512		=	{ 46,szCubeHash_512,		HASH_BYTES_512,	HASH_BITS_512,	CubeHash_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Echo_224			=	{ 47,szEcho_224,			HASH_BYTES_224,	HASH_BITS_224,	Echo_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Echo_256			=	{ 48,szEcho_256,			HASH_BYTES_256,	HASH_BITS_256,	Echo_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Echo_384			=	{ 49,szEcho_384,			HASH_BYTES_384,	HASH_BITS_384,	Echo_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Echo_512			=	{ 50,szEcho_512,			HASH_BYTES_512,	HASH_BITS_512,	Echo_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Fugue_224		=	{ 51,szFugue_224,			HASH_BYTES_224,	HASH_BITS_224,	Fugue_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Fugue_256		=	{ 52,szFugue_256,			HASH_BYTES_256,	HASH_BITS_256,	Fugue_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Fugue_384		=	{ 53,szFugue_384,			HASH_BYTES_384,	HASH_BITS_384,	Fugue_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Fugue_512		=	{ 54,szFugue_512,			HASH_BYTES_512,	HASH_BITS_512,	Fugue_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Groestl_224		=	{ 55,szGrostl_224,			HASH_BYTES_224,	HASH_BITS_224,	Groestl_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Groestl_256		=	{ 56,szGrostl_256,			HASH_BYTES_256,	HASH_BITS_256,	Groestl_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Groestl_384		=	{ 57,szGrostl_384,			HASH_BYTES_384,	HASH_BITS_384,	Groestl_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Groestl_512		=	{ 58,szGrostl_512,			HASH_BYTES_512,	HASH_BITS_512,	Groestl_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Hamsi_224		=	{ 59,szHamsi_224,			HASH_BYTES_224,	HASH_BITS_224,	Hamsi_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Hamsi_256		=	{ 60,szHamsi_256,			HASH_BYTES_256,	HASH_BITS_256,	Hamsi_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Hamsi_384		=	{ 61,szHamsi_384,			HASH_BYTES_384,	HASH_BITS_384,	Hamsi_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Hamsi_512		=	{ 62,szHamsi_512,			HASH_BYTES_512,	HASH_BITS_512,	Hamsi_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_3_128		=	{ 63,szHaval_3_128,			HASH_BYTES_128,	HASH_BITS_128,	Haval_3_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_3_160		=	{ 64,szHaval_3_160,			HASH_BYTES_160,	HASH_BITS_160,	Haval_3_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_3_192		=	{ 65,szHaval_3_192,			HASH_BYTES_192,	HASH_BITS_192,	Haval_3_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_3_224		=	{ 66,szHaval_3_224,			HASH_BYTES_224,	HASH_BITS_224,	Haval_3_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_3_256		=	{ 67,szHaval_3_256,			HASH_BYTES_256,	HASH_BITS_256,	Haval_3_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_4_128		=	{ 68,szHaval_4_128,			HASH_BYTES_128,	HASH_BITS_128,	Haval_4_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_4_160		=	{ 69,szHaval_4_160,			HASH_BYTES_160,	HASH_BITS_160,	Haval_4_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_4_192		=	{ 70,szHaval_4_192,			HASH_BYTES_192,	HASH_BITS_192,	Haval_4_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_4_224		=	{ 71,szHaval_4_224,			HASH_BYTES_224,	HASH_BITS_224,	Haval_4_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_4_256		=	{ 72,szHaval_4_256,			HASH_BYTES_256,	HASH_BITS_256,	Haval_4_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_5_128		=	{ 73,szHaval_5_128,			HASH_BYTES_128,	HASH_BITS_128,	Haval_5_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_5_160		=	{ 74,szHaval_5_160,			HASH_BYTES_160,	HASH_BITS_160,	Haval_5_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_5_192		=	{ 75,szHaval_5_192,			HASH_BYTES_192,	HASH_BITS_192,	Haval_5_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_5_224		=	{ 76,szHaval_5_224,			HASH_BYTES_224,	HASH_BITS_224,	Haval_5_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Haval_5_256		=	{ 77,szHaval_5_256,			HASH_BYTES_256,	HASH_BITS_256,	Haval_5_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Jh_224			=	{ 78,szJh_224,				HASH_BYTES_224,	HASH_BITS_224,	Jh_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Jh_256			=	{ 79,szJh_256,				HASH_BYTES_256,	HASH_BITS_256,	Jh_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Jh_384			=	{ 80,szJh_384,				HASH_BYTES_384,	HASH_BITS_384,	Jh_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Jh_512			=	{ 81,szJh_512,				HASH_BYTES_512,	HASH_BITS_512,	Jh_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Keccak_224		=	{ 82,szKeccak_224,			HASH_BYTES_224,	HASH_BITS_224,	Keccak_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Keccak_256		=	{ 83,szKeccak_256,			HASH_BYTES_256,	HASH_BITS_256,	Keccak_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Keccak_384		=	{ 84,szKeccak_384,			HASH_BYTES_384,	HASH_BITS_384,	Keccak_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Keccak_512		=	{ 85,szKeccak_512,			HASH_BYTES_512,	HASH_BITS_512,	Keccak_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Luffa_224		=	{ 86,szLuffa_224,			HASH_BYTES_224,	HASH_BITS_224,	Luffa_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Luffa_256		=	{ 87,szLuffa_256,			HASH_BYTES_256,	HASH_BITS_256,	Luffa_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Luffa_384		=	{ 88,szLuffa_384,			HASH_BYTES_384,	HASH_BITS_384,	Luffa_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Luffa_512		=	{ 89,szLuffa_512,			HASH_BYTES_512,	HASH_BITS_512,	Luffa_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Maraca_128		=	{ 90,szMaraca_128,			HASH_BYTES_128,	HASH_BITS_128,	Maraca_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Md2_128			=	{ 91,szMd_2_128,			HASH_BYTES_128,	HASH_BITS_128,	Md2_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md4_128			=	{ 92,szMd_4_128,			HASH_BYTES_128,	HASH_BITS_128,	Md4_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md5_128			=	{ 93,szMd_5_128,			HASH_BYTES_128,	HASH_BITS_128,	Md5_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md5Md5_A_128		=	{ 94,szMd5Md5_A_128,		HASH_BYTES_128,	HASH_BITS_128,	Md5Md5_A_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Md5Md5_N_128		=	{ 95,szMd5Md5_N_128,		HASH_BYTES_128,	HASH_BITS_128,	Md5Md5_N_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Md5Sha1_A_128	=	{ 96,szMd_5_Sha1_A_128,		HASH_BYTES_128,	HASH_BITS_128,	Md5Sha1_A_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Md5Sha1_N_128	=	{ 97,szMd_5_Sha1_N_128,		HASH_BYTES_128,	HASH_BITS_128,	Md5Sha1_N_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Md6_128			=	{ 98,szMd_6_128,			HASH_BYTES_128,	HASH_BITS_128,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md6_160			=	{ 99,szMd_6_160,			HASH_BYTES_160,	HASH_BITS_160,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md6_192			=	{100,szMd_6_192,			HASH_BYTES_192,	HASH_BITS_192,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md6_224			=	{101,szMd_6_224,			HASH_BYTES_224,	HASH_BITS_224,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md6_256			=	{102,szMd_6_256,			HASH_BYTES_256,	HASH_BITS_256,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md6_384			=	{103,szMd_6_384,			HASH_BYTES_384,	HASH_BITS_384,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Md6_512			=	{104,szMd_6_512,			HASH_BYTES_512,	HASH_BITS_512,	Md6_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Panama_256		=	{105,szPanama_256,			HASH_BYTES_256,	HASH_BITS_256,	Panama_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_RadioGatun_32_256=	{106,szRadioGatun_256,		HASH_BYTES_256,	HASH_BITS_256,	RadioGatun32_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_RadioGatun_64_256=	{107,szRadioGatun_64,		HASH_BYTES_256,	HASH_BITS_256,	RadioGatun64_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_RipeMd_128		=	{108,szRipeMd_128,			HASH_BYTES_128,	HASH_BITS_128,	RipeMd_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_RipeMd_160		=	{109,szRipeMd_160,			HASH_BYTES_160,	HASH_BITS_160,	RipeMd_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Sarmal_224		=	{110,szSarmal_224,			HASH_BYTES_224,	HASH_BITS_224,	Sarmal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Sarmal_256		=	{111,szSarmal_256,			HASH_BYTES_256,	HASH_BITS_256,	Sarmal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Sarmal_384		=	{112,szSarmal_384,			HASH_BYTES_384,	HASH_BITS_384,	Sarmal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Sarmal_512		=	{113,szSarmal_512,			HASH_BYTES_512,	HASH_BITS_512,	Sarmal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Sha0_160			=	{114,szSha_0_160,			HASH_BYTES_160,	HASH_BITS_160,	Sha0_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Sha1_160			=	{115,szSha_1_160,			HASH_BYTES_160,	HASH_BITS_160,	Sha1_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Sha1Md5_A_160	=	{116,szSha_1_Md5_A_160,		HASH_BYTES_160,	HASH_BITS_160,	Sha1Md5_A_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Sha1Md5_N_160	=	{117,szSha_1_Md5_N_160,		HASH_BYTES_160,	HASH_BITS_160,	Sha1Md5_N_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Sha1Sha1_A_160	=	{118,szSha_1_Sha1_A_160,	HASH_BYTES_160,	HASH_BITS_160,	Sha1Sha1_A_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Sha1Sha1_N_160	=	{119,szSha_1_Sha1_N_160,	HASH_BYTES_160,	HASH_BITS_160,	Sha1Sha1_N_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Sha2_224			=	{120,szSha_2_224,			HASH_BYTES_224,	HASH_BITS_224,	Sha_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Sha2_256			=	{121,szSha_2_256,			HASH_BYTES_256,	HASH_BITS_256,	Sha_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Sha2_384			=	{122,szSha_2_384,			HASH_BYTES_384,	HASH_BITS_384,	Sha_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Sha2_512			=	{123,szSha_2_512,			HASH_BYTES_512,	HASH_BITS_512,	Sha_Db_Insert,			NULL,NULL} ;
DB_INFOS	Db_Shabal_192		=	{124,szShabal_192,			HASH_BYTES_192,	HASH_BITS_192,	Shabal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shabal_224		=	{125,szShabal_224,			HASH_BYTES_224,	HASH_BITS_224,	Shabal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shabal_256		=	{126,szShabal_256,			HASH_BYTES_256,	HASH_BITS_256,	Shabal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shabal_384		=	{127,szShabal_384,			HASH_BYTES_384,	HASH_BITS_384,	Shabal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shabal_512		=	{128,szShabal_512,			HASH_BYTES_512,	HASH_BITS_512,	Shabal_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shavite_224		=	{129,szShavite_224,			HASH_BYTES_224,	HASH_BITS_224,	Shavite_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shavite_256		=	{130,szShavite_256,			HASH_BYTES_256,	HASH_BITS_256,	Shavite_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shavite_384		=	{131,szShavite_384,			HASH_BYTES_384,	HASH_BITS_384,	Shavite_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Shavite_512		=	{132,szShavite_512,			HASH_BYTES_512,	HASH_BITS_512,	Shavite_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Skein_224		=	{133,szSkein_224,			HASH_BYTES_224,	HASH_BITS_224,	Skein_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Skein_256		=	{134,szSkein_256,			HASH_BYTES_256,	HASH_BITS_256,	Skein_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Skein_384		=	{135,szSkein_384,			HASH_BYTES_384,	HASH_BITS_384,	Skein_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Skein_512		=	{136,szSkein_512,			HASH_BYTES_512,	HASH_BITS_512,	Skein_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_StreamHash_224	=	{137,szStreamHash_224,		HASH_BYTES_224,	HASH_BITS_224,	StreamHash_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_StreamHash_256	=	{138,szStreamHash_256,		HASH_BYTES_256,	HASH_BITS_256,	StreamHash_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_StreamHash_384	=	{139,szStreamHash_384,		HASH_BYTES_384,	HASH_BITS_384,	StreamHash_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_StreamHash_512	=	{140,szStreamHash_512,		HASH_BYTES_512,	HASH_BITS_512,	StreamHash_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Tiger_192		=	{141,szTiger_192,			HASH_BYTES_192,	HASH_BITS_192,	Tiger_Db_Insert,		NULL,NULL} ;
DB_INFOS	Db_Waterfall_512	=	{142,szWaterfall_512,		HASH_BYTES_512,	HASH_BITS_512,	Waterfall_Db_Insert,	NULL,NULL} ;
DB_INFOS	Db_Whirlpool_512	=	{143,szWhirlpool_512,		HASH_BYTES_512,	HASH_BITS_512,	Whirlpool_Db_Insert,	NULL,NULL} ;

PASSWORD	lpPassword[]		=	{
										{ 1, 1,"01"},{ 2, 2,"02"},{ 3, 3,"03"},{ 4, 4,"04"},
										{ 5, 5,"05"},{ 6, 6,"06"},{ 7, 7,"07"},{ 8, 8,"08"},
										{ 9, 9,"09"},{10,10,"10"},{11,11,"11"},{12,12,"12"},
										{13,13,"13"},{14,14,"14"},{15,15,"15"},{16,16,"16"},
										{00,00,"00"}
									} ;

HASHSIZE	lpHashSize[]		=	{
										{ 1, 128," 128"},{ 2, 160," 160"},{ 3, 192," 192"},
										{ 4, 224," 224"},{ 5, 256," 256"},{ 6, 288," 288"},
										{ 7, 320," 320"},{ 8, 384," 384"},
										{ 9, 448," 448"},
										{10, 512," 512"},{11, 576," 576"},
										{12, 640," 640"},
										{13,1024,"1024"},
										{00,0000,"0000"}
									} ;

LPALPHABET	lpAlphabet[]		=	{
										&Alphabet_001,&Alphabet_002,&Alphabet_003,&Alphabet_004,
										&Alphabet_005,&Alphabet_006,&Alphabet_007,&Alphabet_008,
										&Alphabet_009,&Alphabet_010,&Alphabet_011,&Alphabet_012,
										&Alphabet_013,&Alphabet_014,&Alphabet_015,&Alphabet_016,
										&Alphabet_017,&Alphabet_018,&Alphabet_019,&Alphabet_020,
										&Alphabet_021,&Alphabet_022,&Alphabet_023,&Alphabet_024,
										&Alphabet_025,&Alphabet_026,&Alphabet_027,&Alphabet_028,
										&Alphabet_029,&Alphabet_030,&Alphabet_031,&Alphabet_032,
										&Alphabet_033,&Alphabet_034,&Alphabet_035,&Alphabet_036,
										&Alphabet_037,&Alphabet_038,&Alphabet_039,&Alphabet_040,
										&Alphabet_041,&Alphabet_042,&Alphabet_043,&Alphabet_044,
										&Alphabet_045,&Alphabet_046,&Alphabet_047,&Alphabet_048,
										&Alphabet_049,&Alphabet_050,&Alphabet_051,&Alphabet_052,
										&Alphabet_053,&Alphabet_054,&Alphabet_055,&Alphabet_056,
										&Alphabet_057,&Alphabet_058,&Alphabet_059,&Alphabet_060,
										&Alphabet_061,&Alphabet_062,&Alphabet_063,&Alphabet_064,
										&Alphabet_065,&Alphabet_066,&Alphabet_067,&Alphabet_068,
										&Alphabet_069,&Alphabet_070,&Alphabet_071,&Alphabet_072,
										&Alphabet_073,&Alphabet_074,&Alphabet_075,&Alphabet_076,
										&Alphabet_077,&Alphabet_078,&Alphabet_079,&Alphabet_080,
										&Alphabet_081,&Alphabet_082,&Alphabet_083,&Alphabet_084,
										&Alphabet_085,&Alphabet_086,&Alphabet_087,&Alphabet_088,
										&Alphabet_089,&Alphabet_090,&Alphabet_091,&Alphabet_092,
										&Alphabet_093,&Alphabet_094,&Alphabet_095,&Alphabet_096,
										&Alphabet_097,&Alphabet_098,&Alphabet_099,&Alphabet_100,
										&Alphabet_101,&Alphabet_102,&Alphabet_103,&Alphabet_104,
										&Alphabet_105,&Alphabet_106,&Alphabet_107,&Alphabet_108,
										&Alphabet_109,&Alphabet_110,&Alphabet_111,&Alphabet_112,
										&Alphabet_113,&Alphabet_114,&Alphabet_115,&Alphabet_116,
										&Alphabet_117,&Alphabet_118,&Alphabet_119,&Alphabet_120,
										&Alphabet_121,&Alphabet_122,&Alphabet_123,&Alphabet_124,
										&Alphabet_125,&Alphabet_126,&Alphabet_127,&Alphabet_128,
										&Alphabet_129,&Alphabet_130,&Alphabet_131,&Alphabet_132,
										&Alphabet_133,&Alphabet_134,&Alphabet_135,&Alphabet_136,
										&Alphabet_137,&Alphabet_138,&Alphabet_139,&Alphabet_140,
										&Alphabet_141,&Alphabet_142,&Alphabet_143,&Alphabet_144,
										&Alphabet_145,&Alphabet_146,&Alphabet_147,&Alphabet_148,
										&Alphabet_149,&Alphabet_150,&Alphabet_151,&Alphabet_152,
										&Alphabet_153,&Alphabet_154,&Alphabet_155,&Alphabet_156,
										&Alphabet_157,&Alphabet_158,&Alphabet_159,&Alphabet_160,
										&Alphabet_161,&Alphabet_162,&Alphabet_163,&Alphabet_164,
										&Alphabet_165,&Alphabet_166,&Alphabet_167,&Alphabet_168,
										&Alphabet_169,&Alphabet_170,&Alphabet_171,&Alphabet_172,
										&Alphabet_173,&Alphabet_174,&Alphabet_175,&Alphabet_176,
										&Alphabet_177,&Alphabet_178,&Alphabet_179,&Alphabet_180,
										&Alphabet_181,&Alphabet_182,&Alphabet_183,&Alphabet_184,
										&Alphabet_185,&Alphabet_186,&Alphabet_187,&Alphabet_188,
										&Alphabet_189,&Alphabet_190,&Alphabet_191,&Alphabet_192,
										&Alphabet_193,&Alphabet_194,&Alphabet_195,&Alphabet_196,
										&Alphabet_197,&Alphabet_198,&Alphabet_199,&Alphabet_200,
										&Alphabet_201,&Alphabet_202,&Alphabet_203,&Alphabet_204,
										&Alphabet_205,&Alphabet_206,&Alphabet_207,&Alphabet_208,
										&Alphabet_209,&Alphabet_210,&Alphabet_211,&Alphabet_212,
										&Alphabet_213,&Alphabet_214,&Alphabet_215,&Alphabet_216,
										&Alphabet_217,&Alphabet_218,&Alphabet_219,&Alphabet_220,
										&Alphabet_221,&Alphabet_222,&Alphabet_223,&Alphabet_224,
										&Alphabet_225,&Alphabet_226,&Alphabet_227,&Alphabet_228,
										&Alphabet_229,&Alphabet_230,&Alphabet_231,&Alphabet_232,
										&Alphabet_233,&Alphabet_234,&Alphabet_235,&Alphabet_236,
										&Alphabet_237,&Alphabet_238,&Alphabet_239,&Alphabet_240,
										&Alphabet_241,&Alphabet_242,&Alphabet_243,&Alphabet_244,
										&Alphabet_245,&Alphabet_246,&Alphabet_247,&Alphabet_248,
										&Alphabet_249,&Alphabet_250,&Alphabet_251,&Alphabet_252,
										&Alphabet_253,&Alphabet_254,&Alphabet_255,&Alphabet_256,
										&Alphabet_257,&Alphabet_258,&Alphabet_259,&Alphabet_260,
										&Alphabet_261,&Alphabet_262,&Alphabet_263,&Alphabet_264,
										&Alphabet_265,&Alphabet_266,&Alphabet_267,&Alphabet_268,
										&Alphabet_269,&Alphabet_270,&Alphabet_271,&Alphabet_272,
										&Alphabet_273,&Alphabet_274,&Alphabet_275,&Alphabet_276,
										&Alphabet_277,&Alphabet_278,&Alphabet_279,&Alphabet_280,
										&Alphabet_281,&Alphabet_282,&Alphabet_283,&Alphabet_284,
										&Alphabet_285,&Alphabet_286,&Alphabet_287,&Alphabet_288,
										&Alphabet_289,&Alphabet_290,&Alphabet_291,&Alphabet_292,
										&Alphabet_293,&Alphabet_294,&Alphabet_295,&Alphabet_296,
										&Alphabet_297,&Alphabet_298,&Alphabet_299,&Alphabet_300,
										&Alphabet_301,&Alphabet_302,&Alphabet_303,&Alphabet_304,
										&Alphabet_305,&Alphabet_306,&Alphabet_307,&Alphabet_308,
										&Alphabet_309,&Alphabet_310,&Alphabet_311,&Alphabet_312,
										&Alphabet_313,&Alphabet_314,&Alphabet_315,&Alphabet_316,
										&Alphabet_317,&Alphabet_318,&Alphabet_319,&Alphabet_320,
										&Alphabet_321,&Alphabet_322,&Alphabet_323,&Alphabet_324,
										&Alphabet_325,&Alphabet_326,&Alphabet_327,&Alphabet_328,
										&Alphabet_329,&Alphabet_330,&Alphabet_331,&Alphabet_332,
										&Alphabet_333,&Alphabet_334,&Alphabet_335,&Alphabet_336,
										&Alphabet_337,&Alphabet_338,&Alphabet_339,&Alphabet_340,
										&Alphabet_341,&Alphabet_342,&Alphabet_343,&Alphabet_344,
										&Alphabet_345,&Alphabet_346,&Alphabet_347,&Alphabet_348,
										&Alphabet_349,&Alphabet_350,&Alphabet_351,&Alphabet_352,
										&Alphabet_353,&Alphabet_354,&Alphabet_355,&Alphabet_356,
										&Alphabet_357,&Alphabet_358,&Alphabet_359,&Alphabet_360,
										&Alphabet_361,&Alphabet_362,&Alphabet_363,&Alphabet_364,
										&Alphabet_365,&Alphabet_366,&Alphabet_367,&Alphabet_368,
										&Alphabet_369,&Alphabet_370,&Alphabet_371,&Alphabet_372,
										&Alphabet_373,&Alphabet_374,
                                         NULL
									} ;

LPDB_INFOS	lpDatabase_128[]	=	{
										&Db_Abacus_128,&Db_Haval_3_128,
										&Db_Haval_4_128,&Db_Haval_5_128,&Db_Maraca_128,&Db_Md2_128,
										&Db_Md4_128,&Db_Md5_128,&Db_Md6_128,&Db_RipeMd_128,
										&Db_Md5Sha1_A_128,&Db_Md5Sha1_N_128,&Db_Md5Md5_A_128,&Db_Md5Md5_N_128,
										NULL
									} ;

LPDB_INFOS	lpDatabase_160[]	=	{
										&Db_Abacus_160,&Db_Haval_3_160,
										&Db_Haval_4_160,&Db_Haval_5_160,&Db_Md6_160,&Db_RipeMd_160,&Db_Sha0_160,
										&Db_Sha1_160,
										&Db_Sha1Md5_A_160,&Db_Sha1Sha1_A_160,
										&Db_Sha1Md5_N_160,&Db_Sha1Sha1_N_160,
										NULL
									} ;

LPDB_INFOS	lpDatabase_192[]	=	{
										&Db_Abacus_192,&Db_Blender_192,
										&Db_Haval_3_192,&Db_Haval_4_192,&Db_Haval_5_192,
										&Db_Md6_192,&Db_Shabal_192,&Db_Tiger_192,
										NULL
									} ;

LPDB_INFOS	lpDatabase_224[]	=	{
										&Db_Abacus_224,&Db_AriRang_224,&Db_Aurora_224,&Db_Blake_224,
										&Db_Blender_224,&Db_Bmw_224,&Db_Cheetah_224,
										&Db_Crunch_224,&Db_CubeHash_224,&Db_Echo_224,&Db_Fugue_224,
										&Db_Groestl_224,&Db_Hamsi_224,&Db_Haval_3_224,&Db_Haval_4_224,
										&Db_Haval_5_224,&Db_Jh_224,&Db_Keccak_224,&Db_Luffa_224,&Db_Md6_224,
										&Db_Sarmal_224,&Db_Sha2_224,&Db_Shabal_224,
										&Db_Shavite_224,&Db_Skein_224,&Db_StreamHash_224,
										NULL
									} ;

LPDB_INFOS	lpDatabase_256[]	=	{
										&Db_Abacus_256,&Db_AriRang_256,&Db_Aurora_256,&Db_Blake_256,
										&Db_Blender_256,&Db_Bmw_256,&Db_Cheetah_256,
										&Db_Crunch_256,&Db_CubeHash_256,&Db_Echo_256,&Db_Fugue_256,
										&Db_Groestl_256,&Db_Hamsi_256,&Db_Haval_3_256,&Db_Haval_4_256,
										&Db_Haval_5_256,&Db_Jh_256,&Db_Keccak_256,&Db_Luffa_256,&Db_Md6_256,
										&Db_Panama_256,&Db_RadioGatun_32_256,&Db_RadioGatun_64_256,
										&Db_Sarmal_256,&Db_Sha2_256,&Db_Shabal_256,
										&Db_Shavite_256,&Db_Skein_256,&Db_StreamHash_256,
										NULL
									} ;

LPDB_INFOS	lpDatabase_288[]	=	{
										&Db_Blender_288,
										NULL
									} ;

LPDB_INFOS	lpDatabase_320[]	=	{
										&Db_Blender_320,
										NULL
									} ;

LPDB_INFOS	lpDatabase_384[]	=	{
										&Db_Abacus_384,&Db_AriRang_384,&Db_Aurora_384,&Db_Blake_384,
										&Db_Blender_384,&Db_Bmw_384,&Db_Cheetah_384,
										&Db_Crunch_384,&Db_CubeHash_384,&Db_Echo_384,&Db_Fugue_384,
										&Db_Groestl_384,&Db_Hamsi_384,&Db_Jh_384,&Db_Keccak_384,
										&Db_Luffa_384,&Db_Md6_384,&Db_Sarmal_384,&Db_Sha2_384,&Db_Shabal_384,
										&Db_Shavite_384,&Db_Skein_384,&Db_StreamHash_384,
										NULL
									} ;

LPDB_INFOS	lpDatabase_448[]	=	{
										&Db_Blender_448,
										NULL
									} ;

LPDB_INFOS	lpDatabase_512[]	=	{
										&Db_Abacus_512,&Db_AriRang_512,&Db_Aurora_512,&Db_Blake_512,
										&Db_Blender_512,&Db_Bmw_512,&Db_Cheetah_512,
										&Db_Crunch_512,&Db_CubeHash_512,&Db_Echo_512,&Db_Fugue_512,
										&Db_Groestl_512,&Db_Hamsi_512,&Db_Jh_512,&Db_Keccak_512,
										&Db_Luffa_512,&Db_Md6_512,&Db_Sarmal_512,&Db_Sha2_512,&Db_Shabal_512,
										&Db_Shavite_512,&Db_Skein_512,
										&Db_StreamHash_512,&Db_Waterfall_512,&Db_Whirlpool_512,
										NULL
									} ;

LPDB_INFOS	lpDatabase_576[]	=	{
										&Db_Blender_576,
										NULL
									} ;

LPDB_INFOS	lpDatabase_640[]	=	{
										&Db_Blender_640,
										NULL
									} ;

LPDB_INFOS	lpDatabase_1024[]	=	{
										&Db_Abacus_1024,
										NULL
									} ;

LPDB_INFOS	lpDatabaseInfos[]	=	{
										&Db_Abacus_128,&Db_Abacus_160,&Db_Abacus_192,&Db_Abacus_224,&Db_Abacus_256,&Db_Abacus_384,&Db_Abacus_512,&Db_Abacus_1024,
										&Db_AriRang_224,&Db_AriRang_256,&Db_AriRang_384,&Db_AriRang_512,
										&Db_Aurora_224,&Db_Aurora_256,&Db_Aurora_384,&Db_Aurora_512,
										&Db_Blake_224,&Db_Blake_256,&Db_Blake_384,&Db_Blake_512,
										&Db_Blender_192,&Db_Blender_224,&Db_Blender_256,&Db_Blender_288,&Db_Blender_320,&Db_Blender_384,&Db_Blender_448,&Db_Blender_512,&Db_Blender_576,&Db_Blender_640,
										&Db_Bmw_224,&Db_Bmw_256,&Db_Bmw_384,&Db_Bmw_512,
										&Db_Cheetah_224,&Db_Cheetah_256,&Db_Cheetah_384,&Db_Cheetah_512,
										&Db_CubeHash_224,&Db_CubeHash_256,&Db_CubeHash_384,&Db_CubeHash_512,
										&Db_Crunch_224,&Db_Crunch_256,&Db_Crunch_384,&Db_Crunch_512,
										&Db_Echo_224,&Db_Echo_256,&Db_Echo_384,&Db_Echo_512,
										&Db_Fugue_224,&Db_Fugue_256,&Db_Fugue_384,&Db_Fugue_512,
										&Db_Groestl_224,&Db_Groestl_256,&Db_Groestl_384,&Db_Groestl_512,
										&Db_Hamsi_224,&Db_Hamsi_256,&Db_Hamsi_384,&Db_Hamsi_512,
										&Db_Haval_3_128,&Db_Haval_3_160,&Db_Haval_3_192,&Db_Haval_3_224,&Db_Haval_3_256,
										&Db_Haval_4_128,&Db_Haval_4_160,&Db_Haval_4_192,&Db_Haval_4_224,&Db_Haval_4_256,
										&Db_Haval_5_128,&Db_Haval_5_160,&Db_Haval_5_192,&Db_Haval_5_224,&Db_Haval_5_256,
										&Db_Jh_224,&Db_Jh_256,&Db_Jh_384,&Db_Jh_512,
										&Db_Keccak_224,&Db_Keccak_256,&Db_Keccak_384,&Db_Keccak_512,
										&Db_Luffa_224,&Db_Luffa_256,&Db_Luffa_384,&Db_Luffa_512,
										&Db_Maraca_128,
										&Db_Md2_128,
										&Db_Md4_128,
										&Db_Md5_128,
										&Db_Md5Md5_N_128,
										&Db_Md6_128,&Db_Md6_160,&Db_Md6_192,&Db_Md6_224,&Db_Md6_256,&Db_Md6_384,&Db_Md6_512,
										&Db_Panama_256,
										&Db_RadioGatun_32_256,&Db_RadioGatun_64_256,
										&Db_RipeMd_128,&Db_RipeMd_160,
										&Db_Sarmal_224,&Db_Sarmal_256,&Db_Sarmal_384,&Db_Sarmal_512,
										&Db_Sha0_160,
										&Db_Sha1_160,
										&Db_Sha2_224,&Db_Sha2_256,&Db_Sha2_384,&Db_Sha2_512,
										&Db_Shabal_192,&Db_Shabal_224,&Db_Shabal_256,&Db_Shabal_384,&Db_Shabal_512,
										&Db_Shavite_224,&Db_Shavite_256,&Db_Shavite_384,&Db_Shavite_512,
										&Db_Skein_224,&Db_Skein_256,&Db_Skein_384,&Db_Skein_512,
										&Db_StreamHash_224,&Db_StreamHash_256,&Db_StreamHash_384,&Db_StreamHash_512,
										&Db_Tiger_192,
										&Db_Waterfall_512,
										&Db_Whirlpool_512,
										&Db_Sha1Sha1_N_160,&Db_Sha1Md5_N_160,&Db_Md5Sha1_N_128,
										NULL
									} ;

DWORD	dwColors[]	=				{
										0xFF0000,0xFFFFFF,0x0000FF,0x00FF00,
										0x00FFFF,0xFF00FF,0xFFFF00,0x000080,
										0x008000,0x008080,0x800000,0x800080,
										0x808000,0x808080,0x0080FF,0x00FF80
									} ;

char		szPrf_Password[]		=	"Password" ;
char		szPrf_Algorithm[]		=	"Algorithm" ;
char		szPrf_Length[]			=	"Length" ;

char		szFindPasswordsClass[]	=	"FindPasswordsClass" ;
char		szFindPasswordsTitle[]	=	"-_- Find & Generate Passwords -_-" ;
char		szNullString[]			=	"\0\0\0" ;

char		szTempDirectory[MAX_PATH] ;
char		szPgmFileName[MAX_PATH] ;
char		szPgmDirectory[MAX_PATH] ;
char		szProfile[MAX_PATH] ;
char		szDataDirectory[MAX_PATH] ;
char		szConfigDirectory[MAX_PATH] ;
char		szLogDirectory[MAX_PATH] ;
char		szResultDirectory[MAX_PATH] ;

NUMBERFMT	NumFmt  = {0,1,3,"."," ",3} ;

HINSTANCE	hInstance ;
HANDLE		hMutex ;
HWND		hWndMain ;
HWND		hDialogs ;

unsigned int	iAlphabetLePlusLong ;
unsigned int	iCodeAlphabetLePlusLong ;
