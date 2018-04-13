/*
 * Autor		: Pablo Luesia
 * Fecha 		: Abril de 2018
 * Archivo		: main.cc
 * Descripcion	: Archivo de especificacion para la practica 5 de 
 *			  	  bioinformatica. Encargado de leer de fichero las 
 * 			  	  sequencias alineadas
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "SeqReader.h"

using namespace std;

/**
 * Devuelve en una matriz la cuenta de cada nucleotido o gap del vector de 
 * secuencias
 * @param sequences (input parameter) All must have the same length
 * @return vector of array representig the matrix
 */
std::vector<std::array<unsigned int, 5>> countNucleotids(
	const std::vector<std::string>& sequence)
{
	unsigned int length = sequence[0].length();
	/*
	 * Cada posicion representa un nucleotido
	 * 1 - G
	 * 2 - A
	 * 3 - T
	 * 4 - C
	 * 5 - Gap
	 */
	std::vector<std::array<unsigned int, 5>> count(length, {{0, 0, 0, 0, 0}});
	
	for (std::vector<std::string>::const_iterator it = sequence.begin();
		it != sequence.end(); it++)
	{
		std::string s = *it;
		
		for (unsigned int i = 0; i < length; i++)
			switch ( s.at(i) ) {
				case 'G': count[i][0]++; break;
				case 'g': count[i][0]++; break;
				case 'A': count[i][1]++; break;
				case 'a': count[i][1]++; break;
				case 'T': count[i][2]++; break;
				case 't': count[i][2]++; break;
				case 'C': count[i][3]++; break;
				case 'c': count[i][3]++; break;
				default: count[i][4]++; break;
			}
	}
	return count;	 
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cerr << "*ERROR ARGUMENTOS* Uso : " << argv[0] 
			<< " nombre_fichero_base nombre_fichero_alineados" << endl;
		return 1;
	}
	
	vector<string> sequences = readFastaSeq(argv[1]);
	vector<string> aligned_sequences = readFastaSeq(argv[2]);
	
	// Busca la secuencia mas larga
	unsigned int longest_seq = 0;
	for (vector<string>::const_iterator it = sequences.begin(); 
			it != sequences.end(); it++)
	{
		unsigned int seq_length = (*it).length();
		if (seq_length > longest_seq)
			longest_seq = seq_length;
	}
	
	// Las secuencias alineadas, tienen todas el mismo tamanyo
	cout << "Ratio de incremento de la longitud: " 
		<< (double)aligned_sequences[0].length() / (double) longest_seq << endl;
		
	vector<array<unsigned int, 5>> count = countNucleotids(aligned_sequences);
	
	ofstream f("frecuencia_nucleotidos.txt");
	f << setw(6) << "Pos" << setw(8) << "G" << setw(8) << "A" << setw(8) << "T" 
		<< setw(8) << "C" << setw(8) << "-" << endl;	
	for (int i = 0; i < count.size(); i++)
	{
		f << setw(6) << i;
		for (int j = 0; j < 5; j++)
			f << setw(8) << count[i][j];
			
		f << endl;
	}
	//f.close();
	
	return 0;
}
