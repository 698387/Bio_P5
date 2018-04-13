/**
 * Autor		: Pablo Luesia
 * Fecha 		: Abril de 2018
 * Archivo		: SeqReader.h
 * Descripcion	: Archivo de especificacion para la practica 5 de 
 *			      bioinformatica. Encargado de leer de fichero las 
 * 			      sequencias alineadas
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/*
 * Devuelve un vector con todas las secuencias del fichero filepath.
 * n_seq indica el numero de secuencias que se quieren leer. Si vale -1, se leen
 * todas las del fichero
 */
std::vector<std::string> readFastaSeq(char* filepath, int n_seq = -1);

/*
 * Devuelve un vector con todas las secuencias del fichero filepath
 * n_seq indica el numero de secuencias que se quieren leer. Si vale -1, se leen
 * todas las del fichero
 */
std::vector<std::string> readFastaSeq(const std::string& filepath,
										int n_seq = -1);


//-------------------------------------------------------------------------------
std::vector<std::string> readFastaSeq(char* filepath, int n_seq)
{

	std::vector<std::string> sequences;
	std::ifstream f;
	f.open(filepath);
	
	unsigned int index;
	if (f.is_open())
	{	
		while (!f.eof())
		{
			std::string s;
			std::getline(f, s);
			
			// Comprueba que no se haya leido una linea vacia
			if (s.length() == 0)
				continue;
			
			// Comprueba si la siguiente linea comienza por ">"
			if (s.at(0) == '>')
			{ // New sequence
				if (n_seq >= 0 && sequences.size() == n_seq)
					break;
					
				sequences.push_back("");
				index = sequences.size() - 1;
			}
			else
			{
				sequences[index] += s;
			}
		}
		f.close();
	} else
		std::cerr << "Could not open the file " << filepath << std::endl;
		
	std::cout << "Read " << sequences.size() << " sequences from " << filepath
			 << std::endl;
	return sequences;
}

//-------------------------------------------------------------------------------
std::vector<std::string> readFastaSeq(const std::string& filepath, int n_seq)
{
	return readFastaSeq(filepath.c_str(), n_seq);
}

