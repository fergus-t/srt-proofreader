//v0.1 - Checks overlap and shows in console. 
//v0.2 - Checks duplicates as well. 
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

bool isInteger(string inputvalue) {
    if (inputvalue.length() == 0) {
        return false;
    }

    for (int i = 0; i < inputvalue.length(); i++) {
        //cout << "char i: " << inputvalue[i] << "  ";
        if (inputvalue.at(i) == '0' || inputvalue.at(i) == '1' || inputvalue.at(i) == '2' || inputvalue.at(i) == '3' || inputvalue.at(i) == '4' || inputvalue.at(i) == '5' || inputvalue.at(i) == '6' || inputvalue.at(i) == '7' || inputvalue.at(i) == '8' || inputvalue.at(i) == '9') {
            //current number is a digit.
            //do nothing.
        }
        else {
            return false;
        }
    }
    return true;
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

    string currentLine = "";
    string previousLine = "";
    string previouspreviousLine = "";

    int currentSubtitleNumber = 0;
    int currentLineNo = 1;
    int lineCount = 1;


    //get the file stream. 
    ifstream inputsrtfile;
    //inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/input.txt", ios::in);
    //inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/normal.srt", ios::in);
    inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/buggy.srt", ios::in);
    //inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/bug.srt", ios::in);
    //inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/duplicate.srt", ios::in);
    //inputsrtfile.open("C:/Users/Fergus Tam/Documents/srt_2/srt_proofreader_2/eng_v2.srt", ios::in);

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

                //used be in case 3:
                //shift the time for the next cycle. 
                previousEndTimeDouble = currentEndTimeDouble;
                previousEndTime = currentEndTime;


                //compare and look for duplicate lines. 

                //cout << previouspreviousLine << " | " << previousLine << " | " << currentLine;

                if (previousLine != "" && previouspreviousLine != "") {
                    //cout << "Checking for duplicates \n";
                    std::size_t found1 = previousLine.find(currentLine);
                    if (found1 != string::npos) {
                        //found a match. 
                        cout << "Suspected duplicated line found at line " << currentLineNo - 1 << " subtitle no. " << currentSubtitleNumber << ": \n  \"" << previousLine << "\" AND \n  \"" << currentLine << "\"\n";
                    }

                    std::size_t found2 = previousLine.find(previouspreviousLine);
                    if (found2 != string::npos) {
                        //found a match. 
                        cout << "Suspected duplicated line found at line " << currentLineNo - 4 << " subtitle no. " << currentSubtitleNumber -1 << ": \n  \"" << previousLine << "\" AND \n  \"" << previouspreviousLine << "\"\n";
                    }


                }

                previouspreviousLine = previousLine;
                previousLine = currentLine;



                break;

            case 1:
                //index line: 
                //cout << "index line: " << lineinput << "\n";
                
                //check whether it is an integer:
                if (isInteger(lineinput)) {
                    //it is an integer. 
                    //convert it into number.
                    currentSubtitleNumber = stoi(lineinput);
                }
                else {
                    cout << "An error occurred when parsing line " << lineCount << ", expected integer, but got \"" << lineinput << "\"\n";
                }

                break;
            case 2: 
                //time.
                //cout << "Checking line: " << lineCount << "\n";
                currentStartTime = lineinput.substr(0, 12);
                currentStartTimeDouble = convertToDouble(currentStartTime);

                currentEndTime = lineinput.substr(17, 12);
                currentEndTimeDouble = convertToDouble(currentEndTime);

                if ((currentStartTimeDouble - previousEndTimeDouble) < 0.000) {
                    //it's an error!
                    cout << "Error at line " << lineCount << ", subtitle " << currentSubtitleNumber << ". Previous end time: " << previousEndTime << " This line starts at: " << currentStartTime << "  Overlap by: " << currentStartTimeDouble - previousEndTimeDouble << "s \n";
                }

                //extract the start and end time, and compare. 
                break;
            case 3:
                //subtitle line.
                //tick.

                //lineinput is the subtitle line. 
                currentLine = lineinput;





                


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
