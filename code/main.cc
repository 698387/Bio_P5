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
#include <cmath>

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
	unsigned int n_seq = 0;
	for (vector<string>::const_iterator it = sequences.begin(); 
			it != sequences.end(); it++)
	{
		unsigned int seq_length = (*it).length();
		if (seq_length > longest_seq)
			longest_seq = seq_length;
	}
	
	n_seq = sequences.size();
	
	// Las secuencias alineadas, tienen todas el mismo tamanyo
	cout << "Ratio de incremento de la longitud: " 
		<< (double)aligned_sequences[0].length() / (double) longest_seq << endl;
		
	vector<array<unsigned int, 5>> count = countNucleotids(aligned_sequences);
	vector<array<double, 4>> freq;
	freq.reserve(count.size());
	
	for (vector<array<unsigned int, 5>>::const_iterator it = count.begin();
		it != count.end(); it++)
	{
		const double n_nucleotids = n_seq - (*it)[4];
		array<double, 4> vn {{(double)(*it)[0] / n_nucleotids,
								(double)(*it)[1] / n_nucleotids,
								(double)(*it)[2] / n_nucleotids,
								(double)(*it)[3] / n_nucleotids }};
		freq.push_back(vn);
	}
		
	ofstream f;
	f.open("idx_conservacion.txt");
	
	f << setw(6) << "Pos" << setw(20) << "Idx_Cons" << endl;
	int id = 1;
	for (vector<array<double, 4>>::const_iterator it = freq.begin(); 
		it != freq.end(); it++)
	{	
		double sum =  ( ((*it)[0] == 0)? 0: (*it)[0] * log((*it)[0]) ) 
					+ ( ((*it)[1] == 0)? 0: (*it)[1] * log((*it)[1]) )
					+ ( ((*it)[2] == 0)? 0: (*it)[2] * log((*it)[2]) )
					+ ( ((*it)[3] == 0)? 0: (*it)[3] * log((*it)[3]) ); 
		f << setw(6) << id << setw(20) << sum << endl;		
		id++;	
	}
	return 0;
}
