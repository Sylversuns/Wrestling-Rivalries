#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <queue>

using namespace std;

/*
Prompt:
Suppose there are two types of professional wrestlers: “Babyfaces” (good guys) and “Heels” (bad guys). 
Between any pair of professional wrestlers, there may or may not be a rivalry. 
Suppose we have a list of n wrestlers and a list of r pairs of rivalries. 
Create an efficient algorithm that determines whether it is possible to designate some of the wrestlers 
as Babyfaces and the remainder as Heels such that each rivalry is between a Babyface and a Heel. 
If it is possible to perform such a designation, the algorithm should produce it.

Input: 
*Input is read in from a file specified in the command line at run time. 
The file contains the number of wrestlers, n, followed by their names, 
the number of rivalries r and rivalries listed in pairs.

Output: 
Results are outputted to the terminal.
-- Yes, if possible, followed by a list of the Babyfaces and another list of the Heels.
-- No, if impossible.
*/

struct wrestler
{
	string name;
	int id;
	string type;
	string color;
};

struct rivalry
{
	string wrestler1;
	string wrestler2;
	int wrestler1id;
	int wrestler2id;
};

// Input is the wrestlers, rivalries, the number of wrestlers, and the number of rivalries.
bool wrestling(wrestler n [], rivalry r [], int sizeofn, int sizeofr)
{
	// Declare a queue of wrestlers, and add the first name, assuming it is a Babyface.
	queue<wrestler> Q;
	n[0].type = "Babyface";
	Q.push(n[0]);
	while (Q.empty() == false)
	{
		// Take a wrestler off the queue
		wrestler z = Q.front();
		Q.pop();
		// Go through the list of rivalries
		for (int a = 0; a < sizeofr; a++)
		{
			// If the wrestler's ID is the first one of the two in the rivalry...
			if (z.id == r[a].wrestler1id)
			{
				// And if the other wrestler's type is unknown...
				if (n[r[a].wrestler2id].type == "Unknown")
				{
					// Make it the opposite type.
					if(z.type == "Babyface")
						n[r[a].wrestler2id].type = "Heel";
                    if(z.type == "Heel")
                        n[r[a].wrestler2id].type = "Babyface";
                    // And add it to the queue.
					Q.push(n[r[a].wrestler2id]);
				}
				// If at any point their types match, return false (impossible to sort).
				if (z.type == n[r[a].wrestler2id].type)
					return false;
			}	

			// Do the same thing for the second wrestler in the rivalry.
            if (z.id == r[a].wrestler2id)
            {       
                if (n[r[a].wrestler1id].type == "Unknown")
                {       
                    if(z.type == "Babyface")
                            n[r[a].wrestler1id].type = "Heel";
                    if(z.type == "Heel")
                            n[r[a].wrestler1id].type = "Babyface";
					Q.push(n[r[a].wrestler1id]);
                }

                if (z.type == n[r[a].wrestler1id].type)
                    return false;
            }
		}

		// If there are any more rivalries where both are unknown, #1 is a Babyface and #2 is a Heel.
		// This is necessary in case there are any "islands" 
		// (wrestlers that only interact with each other, not the wider group).
		for (int b = 0; b < sizeofr; b++)
		{
			if(n[r[b].wrestler1id].type == "Unknown" && n[r[b].wrestler2id].type == "Unknown")
			{
				n[r[b].wrestler1id].type = "Babyface";
				Q.push(n[r[b].wrestler1id]);
			}
		}
	}
	return true;
}

// The program will open the file, read in the number of wrestlers and then their names,
// and then read in the number of rivalries and then who the two rivals are for each.
int main()
{
	ifstream inputfile("wrestler.txt"); // Set up input file.
	if (!inputfile.is_open()){
		cout << "Input file could not be opened." << endl;
		return 1;
	}
	
	int sizeofn;
	int sizeofr;
	
	inputfile >> sizeofn;
	wrestler* n = new wrestler[sizeofn]; // Make dynamic array
	for (int i = 0; i < sizeofn; i++) // Read in the wrestlers, and assign ids.
	{
		inputfile >> n[i].name;
		n[i].id = i;
		n[i].type = "Unknown";
	}

	inputfile >> sizeofr;
	rivalry* r = new rivalry[sizeofr];	
        for (int j = 0; j < sizeofr; j++) // Read in the rivalries.
        {
                inputfile >> r[j].wrestler1;
                inputfile >> r[j].wrestler2;
        }

    // Go through the rivalry list, fill out the IDs of each wrestler in the structs.
	for (int m = 0; m < sizeofr; m++)
	{
		for (int p = 0; p < sizeofn; p++)
		{
			if (r[m].wrestler1 == n[p].name)
				r[m].wrestler1id = n[p].id;
			if (r[m].wrestler2 == n[p].name)
                r[m].wrestler2id = n[p].id;
		}
	}

    // Call the main function, which will solve the problem.
    // Input is the wrestlers, rivalries, the number of wrestlers, and the number of rivalries.
	bool result = wrestling (n, r, sizeofn, sizeofr);

    // If the result is true, output "Yes" and the lists.
	if (result == true)
	{
		cout << endl << "Yes, this is possible." << endl << endl; // Output
	
		cout << "Babyfaces: " << endl;
        	for (int k = 0; k < sizeofn; k++)
        	{
			if (n[k].type == "Babyface")
        	        	cout << n[k].name << endl;
        	}
		
		cout << endl << "Heels: " << endl;
		for (int k = 0; k < sizeofn; k++)
		{
			if (n[k].type == "Heel")
				cout << n[k].name << endl;
		}
	}

	// If it's not possible (the result is false), say so.
	else
	{
		cout << endl << "This is impossible." << endl;
	}

	delete [] n; // Memory cleanup
	delete [] r; 

	inputfile.close(); // Close the file.

	cout << endl;

	return 0;
}
