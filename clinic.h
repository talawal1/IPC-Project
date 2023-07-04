/*/////////////////////////////////////////////////////////////////////////
						Assignment 1 - Milestone 3
Full Name  : Teslim Ajibola Lawal
Email      : talawal1@myseneca.ca
Section    : ZCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.
#ifndef CLINIC_H
#define CLINIC_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10


// MS#3 Additional macro's:
// ToDo:
#define ALL_RECORDS 1
#define DATE_RECORDS 0

#define START_YEAR 2023
#define END_YEAR 9999

#define LEAST_PATIENT_NUMBER 0
#define MAX_PATIENT_NUMBER 99999

#define JAN 1
#define DEC 12

#define START_HOUR 0
#define END_HOUR 23

#define START_MINUTE 0
#define END_MINUTE 59

#define MINUTE_INTERVAL 30

#define START_TIME 10
#define END_TIME 14

//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
// (Copy your code from MS#2)
struct Phone {
	char description[PHONE_DESC_LEN + 1];
	char number[PHONE_LEN + 1];
};

// Data type: Patient 
// (Copy your code from MS#2)
struct Patient {
	int patientNumber;
	char name[NAME_LEN + 1];
	struct Phone phone;
};


// ------------------- MS#3 -------------------

// Data type: Time
// ToDo:
struct Time {
	int hour;
	int min;
};

// Data type: Date
// ToDo:
struct Date {
	int year;
	int month;
	int day;
};

// Data type: Appointment
// ToDo:
struct Appointment {
	int patientNumber;
	struct Date date;
	struct Time time;
};


// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
	struct Patient* patients;
	int maxPatient;
	struct Appointment* appointments;
	int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
	const struct Appointment* appoint,
	int includeDateField);


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(const struct ClinicData* data); // CROSSCHECK

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData* data);

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatients);

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatients);


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
	const struct Patient patient[], int max);

//MS3
// Determine whether a year is a leap year or not. Returns 1 if true and 0 if not a leap year
int isLeapYear(int year);

// Determine end date of a month based on year and month provided
int determineEndDateMonth(int year, int month);

// Determine whether an appointment has the same date as user entered date. Returns 1 if true and 0 if false
int checkAppointmentDate(struct Appointment* appointment, struct Date* userEnteredDate);

// Check if an appointment timeslot has been occupied
int checkIfAppointmentExists(struct Appointment appointments[], int maxAppointments, struct Date* userEnteredDate, struct Time* userEnteredTime);

// Sort an array based on the parameter specified
void bubbleSort(struct Appointment appointments[], int maxAppointments, char sortBy);

// Sort appointments in ascending order
void sortAppointments(struct Appointment appointments[], int maxAppointments);
//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

// Prompt user to enter year, month and date. Validate entered values
void inputDate(int* year, int *month, int* day);

// Prompt user to input time
void inputTime(int* hour, int* minute);

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H