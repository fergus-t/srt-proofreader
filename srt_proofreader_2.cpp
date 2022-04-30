//v0.1 - Checks overlap and shows in console. 
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double convertToDouble(string inputTime) {
    int h = stoi(inputTime.substr(0, 2));
    int m = stoi(inputTime.substr(3, 2));
    int s = stoi(inputTime.substr(6, 2));
    int ms = stoi(inputTime.substr(9, 3));
    double result = h * 3600.0 + m * 60.0 + s + ms / 1000.0;
    //cout << "Input: " << inputTime << " Output: " << result;
    return result;
}


int main() {
    cout << "SRT Proofreader\n";


    //declare variables: 
    string previousEndTime = "00:00:00,000";
    double previousEndTimeDouble = 0;

    string currentStartTime;
    double currentStartTimeDouble;

    string currentEndTime;
    double currentEndTimeDouble;

    int currentSubtitleNumber = 0;
    int currentLineNo = 1;
    int lineCount = 1;


    //get the file stream. 
    ifstream inputsrtfile;
    //inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/input.txt", ios::in);
    inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/chi_v2.srt", ios::in);

    cout << "opening the file\n";

    //checking whether file is open:
    if (inputsrtfile.is_open()) {
        
        //file is open. 
        cout << "successfully opened the file \n";
        string lineinput;
        while (getline(inputsrtfile, lineinput)) {
            // lineinput now contians the current line.

            switch (currentLineNo % 4)
            {
            case 0:
                //blank line. do nothing.
                break;
            case 1:
                //index line: 
                //cout << "index line: " << lineinput << "\n";
                //currentSubtitleNumber = stoi(lineinput);

                break;
            case 2: 
                //time.
                currentStartTime = lineinput.substr(0, 12);
                currentStartTimeDouble = convertToDouble(currentStartTime);

                currentEndTime = lineinput.substr(17, 12);
                currentEndTimeDouble = convertToDouble(currentEndTime);

                if ((currentStartTimeDouble - previousEndTimeDouble) < 0.000) {
                    //it's an error!
                    cout << "Error at line " << lineCount << ". Previous end time: " << previousEndTime << " Next start line: " << currentStartTime << "  Overlap by: " << currentStartTimeDouble - previousEndTimeDouble << "s \n";
                }

                //extract the start and end time, and compare. 
                break;
            case 3:
                //subtitle line.
                //tick.
                previousEndTimeDouble = currentEndTimeDouble;
                previousEndTime = currentEndTime;


                break;
            
            default:
                break;
            }


            //cout << currentLineNo << ": " << lineinput << "\n";
            currentLineNo++;
            lineCount++;
        }
        inputsrtfile.close();

        cout << "End of validation. ";
    }
    else {
        cout << "File is not open\n";
    }

    return 0;
}











// srt_proofreader_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//
//int main()
//{
//    std::cout << "Hello World!\n";
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
