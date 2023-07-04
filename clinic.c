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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

#include <string.h>
//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
	printf("Pat.# Name            Phone#\n"
		"----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
	if (fmt == FMT_FORM)
	{
		printf("Name  : %s\n"
			"Number: %05d\n"
			"Phone : ", patient->name, patient->patientNumber);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
	else
	{
		printf("%05d %-15s ", patient->patientNumber,
			patient->name);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
	printf("Clinic Appointments for the Date: ");

	if (isAllRecords)
	{
		printf("<ALL>\n\n");
		printf("Date       Time  Pat.# Name            Phone#\n"
			"---------- ----- ----- --------------- --------------------\n");
	}
	else
	{
		printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
		printf("Time  Pat.# Name            Phone#\n"
			"----- ----- --------------- --------------------\n");
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
	const struct Appointment* appoint,
	int includeDateField)
{
	if (includeDateField)
	{
		printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
			appoint->date.day);
	}
	printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
		patient->patientNumber, patient->name);

	displayFormattedPhone(patient->phone.number);

	printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
	int selection;

	do {
		printf("Veterinary Clinic System\n"
			"=========================\n"
			"1) PATIENT     Management\n"
			"2) APPOINTMENT Management\n"
			"-------------------------\n"
			"0) Exit System\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');
		switch (selection)
		{
		case 0:
			printf("Are you sure you want to exit? (y|n): ");
			selection = !(inputCharOption("yn") == 'y');
			putchar('\n');
			if (!selection)
			{
				printf("Exiting system... Goodbye.\n\n");
			}
			break;
		case 1:
			menuPatient(data->patients, data->maxPatient);
			break;
		case 2:
			menuAppointment(data);
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
	int selection;

	do {
		printf("Patient Management\n"
			"=========================\n"
			"1) VIEW   Patient Data\n"
			"2) SEARCH Patients\n"
			"3) ADD    Patient\n"
			"4) EDIT   Patient\n"
			"5) REMOVE Patient\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 5);
		putchar('\n');
		switch (selection)
		{
		case 1:
			displayAllPatients(patient, max, FMT_TABLE);
			suspend();
			break;
		case 2:
			searchPatientData(patient, max);
			break;
		case 3:
			addPatient(patient, max);
			suspend();
			break;
		case 4:
			editPatient(patient, max);
			break;
		case 5:
			removePatient(patient, max);
			suspend();
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
	int selection;

	do {
		printf("Edit Patient (%05d)\n"
			"=========================\n"
			"1) NAME : %s\n"
			"2) PHONE: ", patient->patientNumber, patient->name);

		displayFormattedPhone(patient->phone.number);

		printf("\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');

		if (selection == 1)
		{
			printf("Name  : ");
			inputCString(patient->name, 1, NAME_LEN);
			putchar('\n');
			printf("Patient record updated!\n\n");
		}
		else if (selection == 2)
		{
			inputPhoneData(&patient->phone);
			printf("Patient record updated!\n\n");
		}

	} while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
	int selection;

	do {
		printf("Appointment Management\n"
			"==============================\n"
			"1) VIEW   ALL Appointments\n"
			"2) VIEW   Appointments by DATE\n"
			"3) ADD    Appointment\n"
			"4) REMOVE Appointment\n"
			"------------------------------\n"
			"0) Previous menu\n"
			"------------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 4);
		putchar('\n');
		switch (selection)
		{
		case 1:
			viewAllAppointments(data);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 2:
			viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 3:
			addAppointment(data->appointments, data->maxAppointments,
				data->patients, data->maxPatient);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 4:
			removeAppointment(data->appointments, data->maxAppointments,
				data->patients, data->maxPatient);  // ToDo: You will need to create this function!
			suspend();
			break;
		}
	} while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) 
{
	int i;
	int recordsFound = 0;
	int tableDisplayed = 0;

	// Loop through the patient array
	for (i = 0; i < max; i++)
	{
		//Check if patient number is not zero
		if ((patient[i].patientNumber) != 0)
		{
			// Display table header if table has not yet been displayed
			if (tableDisplayed == 0)
			{
				displayPatientTableHeader();
				tableDisplayed = 1;
			}
			displayPatientData(&patient[i], fmt);
			recordsFound = 1;
		}
	}
	printf("\n");

	i = 0;
	if (recordsFound == 0) {
		printf("*** No records found ***\n");
	}

	return;
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) 
{
	int searchOption = 0;
	int done = 0;

	while (done != 1) {
		// Display menu to user
		printf("Search Options\n");
		printf("==========================\n");
		printf("1) By patient number\n");
		printf("2) By phone number\n");
		printf("..........................\n");
		printf("0) Previous menu\n");
		printf("..........................\n");

		//Prompt user for search option
		printf("Selection: ");
		searchOption = inputIntRange(0, 2);

		printf("\n");

		if (searchOption == 1)
		{
			searchPatientByPatientNumber(patient, max);

		}

		else if (searchOption == 2)
		{
			searchPatientByPhoneNumber(patient, max);
		}

		else if (searchOption == 0)
		{
			done = 1;
		}

		if (searchOption == 1 || searchOption == 2)
		{
			suspend();
		}
	}
	return;
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
	int i = 0;
	int done = 0; // Flag variable
	int freeElement = 0;
	int freeIndex = 0;

	while ((i < max) && done != 1)
	{
		if (((patient[i]).patientNumber) == 0)
		{
			freeElement = 1; //Signifies there is a free element for a new record
			done = 1;
			freeIndex = i;
		}
		i += 1;
	}
	i = 0;

	if (freeElement == 1)
	{
		// Generate the next patient number for new patient to be added
		(patient[freeIndex]).patientNumber = nextPatientNumber(patient, max);

		// User is promoted to enter patient details
		inputPatient(&(patient[freeIndex]));
		printf("*** New patient record added ***\n\n");
	}

	else
	{
		printf("ERROR: Patient listing is FULL!\n\n");
	}
	freeElement = 0;
	done = 0;
	freeIndex = 0;

	return;
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
	int patientNumber = 0;
	int patientRecordIndex = 0;
	printf("Enter the patient number: ");
	patientNumber = inputIntRange(LEAST_PATIENT_NUMBER, MAX_PATIENT_NUMBER);
	printf("\n");

	patientRecordIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

	if (patientRecordIndex != -1)
	{
		menuPatientEdit(&(patient[patientRecordIndex]));

	}

	// Patient record not found. Display error message
	else
	{
		printf("ERROR: Patient record not found!\n");
	}
	return;
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
	int patientNumber = 0;
	int patientRecordIndex = 0;
	char userChoice = 0;
	struct Patient emptyPatient = { 0, "", {"0", "0"} };
	const char validCharacters[] = { 'y', 'n', '\0' };

	printf("Enter the patient number: ");
	patientNumber = inputIntRange(LEAST_PATIENT_NUMBER, MAX_PATIENT_NUMBER);

	patientRecordIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

	if (patientRecordIndex != -1)
	{
		printf("\n");
		displayPatientData(&(patient[patientRecordIndex]), FMT_FORM);
		printf("\nAre you sure you want to remove this patient record? (y/n): ");
		userChoice = inputCharOption(validCharacters);

		// Delete patient record if user confirms
		if (userChoice == 'y')
		{
			patient[patientRecordIndex] = emptyPatient;
			printf("Patient record has been removed!\n\n");
		}

		// Don't delete patient record
		else
		{
			printf("Operation aborted.\n\n");
		}
	}

	// Patient record not found
	else
	{
		printf("\nERROR: Patient record not found!\n\n");
	}

	return;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(const struct ClinicData* data) {
	int tableDisplayed = 0, i;
	int maxAppointments = data->maxAppointments;
	int patientNumber = 0, patientIndex = 0;

	// Sort the appointments array
	sortAppointments(data->appointments, data->maxAppointments);

	// Loop through clinic data
	for (i = 0; i < maxAppointments; i++) {
		// Display table if not yet displayed
		if (tableDisplayed == 0) {
			displayScheduleTableHeader(&((data->appointments[i]).date), ALL_RECORDS);
			tableDisplayed = 1;
		}
		if (((data->appointments[i]).date.year) != 0) { // Check that appointment time slot is not empty before displaying it
			patientNumber = (data->appointments[i]).patientNumber;
			patientIndex = findPatientIndexByPatientNum(patientNumber, data->patients, data->maxPatient);
			displayScheduleData(&(data->patients[patientIndex]), &(data->appointments[i]), ALL_RECORDS);
		}
	}
	printf("\n");
	return;
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData* data) {
	int year = 0, month = 0, day = 0;
	int tableDisplayed = 0, i;
	int maxAppointments = data->maxAppointments;
	int patientNumber = 0, patientIndex = 0;
	struct Date userEnteredDate = { 0 };
	int appointmentMatchesDate = 0, appointmentFound = 0;

	inputDate(&year, &month, &day); // Prompt user to input date

	// Set values in date to user entered values that have been validated
	(userEnteredDate).year = year;
	(userEnteredDate).month = month;
	(userEnteredDate).day = day;

	// Sort the appointments array
	sortAppointments(data->appointments, data->maxAppointments);

	// Loop through clinic data
	for (i = 0; i < maxAppointments; i++) {
		// Determine whether an appointment date is the same as user entered date
		appointmentMatchesDate = checkAppointmentDate(&(data->appointments[i]), &userEnteredDate);

		// Appointment that matches date is found
		if (appointmentMatchesDate == 1) {
			appointmentFound = 1;

			// Display table if not yet displayed
			if (tableDisplayed == 0) {
				printf("\n");
				displayScheduleTableHeader(&userEnteredDate, 0);
				tableDisplayed = 1;
			}
			patientNumber = (data->appointments[i]).patientNumber;
			patientIndex = findPatientIndexByPatientNum(patientNumber, data->patients, data->maxPatient);
			displayScheduleData(&(data->patients[patientIndex]), &(data->appointments[i]), DATE_RECORDS);
		}
	}

	if (appointmentFound == 0) { // No appointment was found
		printf("No appointment of this date was found!");
	}
	printf("\n");
	return;
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatients) {
	int patientIndex = 0, appointmentExists = 0;
	int enteredPatientNumber = 0;
	int done = 0, i = 0, appointmentBooked = 0; // Flag variable
	int freeElement = 0, freeIndex = 0;
	struct Date userEnteredDate = { 0 };
	struct Time userEnteredTime = { 0 };

	// Prompt user to enter patient number and validate entered number
	printf("Patient Number: ");
	enteredPatientNumber = inputIntRange(LEAST_PATIENT_NUMBER, MAX_PATIENT_NUMBER);


	// Store patient index based on patientNumber and patient array
	patientIndex = findPatientIndexByPatientNum(enteredPatientNumber, patients, maxPatients);

	// Check if patient record exists or not
	if (patientIndex == -1) { // Patient record does not exist
		printf("ERROR: Patient record not found!\n\n");
	}

	else { // Patient record exists
			while (appointmentBooked != 1) {
			// Ask user for date and time until a free appointment spot is gotten
			inputDate(&(userEnteredDate.year), &(userEnteredDate.month), &(userEnteredDate.day)); // Prompt user to input date
			inputTime(&(userEnteredTime.hour), &(userEnteredTime.min)); // Prompt user to input time


			// Check that appointment time has not been booked yet
			appointmentExists = checkIfAppointmentExists(appointments, maxAppointments, &userEnteredDate, &userEnteredTime);
			if (appointmentExists == 0)
			{
				while ((i < maxAppointments) && done != 1)
				{
					if (((appointments[i]).date.year) == 0 && ((appointments[i]).date.month) == 0 && ((appointments[i]).date.day) == 0 && ((appointments[i]).time.hour) == 0 && ((appointments[i]).time.min == 0))
					{
						freeElement = 1; //Signifies there is a free element for a new appointment record
						done = 1;
						freeIndex = i;
					}
					i += 1;
				}
				i = 0;

				if (freeElement == 1)
				{
					// Add the appointment record of the user
					appointments[freeIndex].patientNumber = enteredPatientNumber;
					appointments[freeIndex].date = userEnteredDate;
					appointments[freeIndex].time = userEnteredTime;

					printf("\n*** Appointment scheduled! ***\n\n");
					appointmentBooked = 1;
				}

				else
				{
					printf("\nERROR: Appointment timeslot is not available!\n\n");
				}
			}
			else
			{
				printf("\nERROR: Appointment timeslot is not available!\n\n");
			}
		}
	}
	return;
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], int maxAppointments, struct Patient patients[], int maxPatients) {
	int enteredPatientNumber = 0;
	int patientIndex = 0, appointmentIndex = 0;
	int year = 0, month = 0, day = 0;
	int done = 0, i;
	char userChoice = 0;
	struct Date userEnteredDate = { 0 };
	const char validCharacters[] = { 'y', 'n', '\0' };


	// Prompt user to enter patient number and validate entered number
	printf("Patient Number: ");
	enteredPatientNumber = inputIntRange(LEAST_PATIENT_NUMBER, MAX_PATIENT_NUMBER);


	// Store patient index based on patientNumber and patient array
	patientIndex = findPatientIndexByPatientNum(enteredPatientNumber, patients, maxPatients);


	// Check if patient record exists or not

	if (patientIndex == -1) { // Patient record does not exist
		printf("ERROR: Patient record not found!\n\n");
	}

	else { // Patient record exists
		inputDate(&year, &month, &day); // Prompt user to input date
		printf("\n");
		// Set values in date to user entered values that have been validated
		(userEnteredDate).year = year;
		(userEnteredDate).month = month;
		(userEnteredDate).day = day;

		//Search for appointment that meets specifications(patientNumber and specific date)
		for (i = 0; i < maxAppointments && done != 1; i++) {
			if ((appointments[i].patientNumber == enteredPatientNumber) && (checkAppointmentDate(&(appointments[i]), &(userEnteredDate)) == 1)) {
				displayPatientData(&(patients[patientIndex]), FMT_FORM);
				appointmentIndex = i;
				done = 1;
			}
		}
		printf("Are you sure you want to remove this appointment (y,n): ");
		userChoice = inputCharOption(validCharacters); // Validate user's entered character
		printf("\n");
		if (userChoice == 'y') {
			appointments[appointmentIndex].patientNumber = 0;
			appointments[appointmentIndex].date = (struct Date){ 0, 0, 0 };
			appointments[appointmentIndex].time = (struct Time){ 0, 0 };

			printf("Appointment record has been removed!\n\n");
		}
	}
	return;
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
	int patientNumber = 0;
	int patientRecordIndex = 0;

	printf("Search by patient number: ");
	patientNumber = inputIntRange(LEAST_PATIENT_NUMBER, MAX_PATIENT_NUMBER);
	printf("\n");

	patientRecordIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

	// Patient record found
	if (patientRecordIndex != -1)
	{
		displayPatientData(&(patient[patientRecordIndex]), FMT_FORM);
		printf("\n");
	}

	else {
		printf("*** No records found ***\n\n");
	}
	return;
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
	char patientPhoneNumber[PHONE_LEN + 1] = { 0 };
	int patientRecordIndex = 0;
	int patientNumber = -1;
	int i;
	int recordFound = 0;
	int tableDisplayed = 0;
	int phoneNumberFound = 0;

	printf("Search by phone number: ");
	inputCString(patientPhoneNumber, PHONE_LEN, PHONE_LEN); // Validate entered phone number

	printf("\n");

	// Search for a phone number in all patients array
	for (i = 0; i < max; i++) {

		// Compare user entered phone number and phone number in record
		if ((strcmp(patientPhoneNumber, ((patient[i].phone).number))) == 0)
		{
			patientNumber = patient[i].patientNumber;
			phoneNumberFound = 1;
		}
		patientRecordIndex = findPatientIndexByPatientNum(patientNumber, patient, max);

		// Display table if table has not yet been booked
		if (tableDisplayed == 0)
		{
			displayPatientTableHeader();
			tableDisplayed = 1;
		}

		// Patient record found
		if (patientRecordIndex != -1 && phoneNumberFound == 1)
		{
			displayPatientData(&(patient[patientRecordIndex]), FMT_TABLE);
			recordFound = 1;
		}
		patientNumber = 0;
		phoneNumberFound = 0;
	}
	if (recordFound == 0) {
		printf("\n*** No records found ***\n\n");
	}
	else {
		printf("\n");
	}
	return;
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) 
{
	int i = 0;

	int largestPatientNumber = 0;

	while ((i < max))
	{

		if (((patient[i]).patientNumber) > largestPatientNumber)
		{
			largestPatientNumber = ((patient[i]).patientNumber);

		}
		i += 1;
	}
	i = 0;
	largestPatientNumber = largestPatientNumber + 1;
	return largestPatientNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) 
{
	int patientIndex = 0;
	int recordFound = 0;
	int i;

	for (i = 0; i < max; i++)
	{
		// Patient number found
		if ((patient[i].patientNumber) == patientNumber)
		{
			patientIndex = i;
			recordFound = 1; //Set recordFound to a true value
		}
	}
	if (recordFound == 0)
	{
		patientIndex = -1;
	}

	return patientIndex;
}


//Determine whether a year is a leap year or not. Returns 1 if true and 0 if not a leap year
int isLeapYear(int year) 
{
	int leapYear = 0;

	// Check if conditions for a leap year are met
	if (((year % 4) == 0 && ((year % 100)) != 0) || ((year % 400) == 0)) {
		leapYear = 1;
	}
	return leapYear;
}

// Determine end date of a month based on year and month provided
int determineEndDateMonth(int year, int month) 
{
	int endDate = 0;
	int leapYear = 0;
	const int FEB = 2, SEP = 9, APR = 4, JUN = 6, NOV = 11;

	// First check if year is a leap year or not 
	leapYear = isLeapYear(year);

	// Check if month is February
	if (month == FEB) {
		// Month is FEB and year is a leap year set endDate to 29
		if (leapYear == 1) {
			endDate = 29;
		}
		// Month is FEB and year is not a leap year set endDate to 28
		else {
			endDate = 28;
		}
	}

	// Month is not FEB
	else {
		// If month is SEP, APR, JUN or NOV, set endDate to 30
		if ((month == SEP) || (month == APR) || (month == JUN) || (month == NOV)) {
			endDate = 30;
		}

		// If any other month set endDate to 31
		else {
			endDate = 31;
		}
	}

	return endDate;
}

// Determine whether an appointment has the same date as user entered date. Returns 1 if true and 0 if false
int checkAppointmentDate(struct Appointment* appointment, struct Date* userEnteredDate) 
{
	int appointmentMatchesDate = 0;

	// Check if year, month and day entered by a user is equal to that of an appointment
	if (((appointment->date).year == userEnteredDate->year) && ((appointment->date.month) == userEnteredDate->month) && (appointment->date.day) == userEnteredDate->day) {
		appointmentMatchesDate = 1;
	}
	return appointmentMatchesDate;
}

// Check if an appointment timeslot has been occupied
int checkIfAppointmentExists(struct Appointment appointments[], int maxAppointments, struct Date* userEnteredDate, struct Time* userEnteredTime)
{
	int i = 0, appointmentExists = 0;

	while (i < maxAppointments)
	{
		if ((checkAppointmentDate(&(appointments[i]), (userEnteredDate)) == 1) && (appointments[i].time.hour) == userEnteredTime->hour && (appointments[i].time.min) == userEnteredTime->min)
		{
			appointmentExists = 1;

		}
		i += 1;
	}

	return appointmentExists;
}

// Sort an array based on the parameter specified
void bubbleSort(struct Appointment appointments[], int maxAppointments, char sortBy)
{
	int i, j;
	struct Appointment temp;
	int firstAppointment = 0;
	int nextAppointment = 0;

	for (i = maxAppointments - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			switch (sortBy)
			{
			// Year
			case 'y':
				firstAppointment = appointments[j].date.year;
				nextAppointment = appointments[j + 1].date.year;
				break;

			// Month
			case 'm':
				firstAppointment = appointments[j].date.month;
				nextAppointment = appointments[j + 1].date.month;
				break;
			
			// Day
			case 'd':
				firstAppointment = appointments[j].date.day;
				nextAppointment = appointments[j + 1].date.day;
				break;
			
			// Hour
			case 'h':
				firstAppointment = appointments[j].time.hour;
				nextAppointment = appointments[j + 1].time.hour;
				break;

			// Minute
			case 'i':
				firstAppointment = appointments[j].time.min;
				nextAppointment = appointments[j + 1].time.min;
				break;

			default:
				firstAppointment = appointments[j].date.year;
				nextAppointment = appointments[j + 1].date.year;
			}

			if (firstAppointment > nextAppointment)
			{
				temp = appointments[j];
				appointments[j] = appointments[j + 1];
				appointments[j + 1] = temp;
			}
		}
	}
}

// Sort appointments in ascending order
void sortAppointments(struct Appointment appointments[], int maxAppointments) 
{
	bubbleSort(appointments, maxAppointments, 'i'); // Sort by minute
	bubbleSort(appointments, maxAppointments, 'h'); // Sort by hour
	bubbleSort(appointments, maxAppointments, 'd'); // Sort by day
	bubbleSort(appointments, maxAppointments, 'm'); // Sort by minute
	bubbleSort(appointments, maxAppointments, 'y'); // Sort by year
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) 
{
	printf("Patient Data Input\n");
	printf("------------------\n");
	printf("Number: %05d\n", patient->patientNumber);

	printf("Name  : ");
	inputCString(patient->name, 1, NAME_LEN);

	printf("\n");

	inputPhoneData(&(patient->phone));

	return;
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {
	int userChoice = 0;
	// Display menu to user
	printf("Phone Information\n");
	printf("-----------------\n");
	printf("How will the patient like to be contacted?\n");
	printf("1. Cell\n");
	printf("2. Home\n");
	printf("3. Work\n");
	printf("4. TBD\n");

	printf("Selection: ");
	userChoice = inputIntRange(1, 4); //User must enter an integer in range of 1-4
	printf("\n");

	switch (userChoice) {
	case 1:
		strncpy(phone->description, "CELL", PHONE_DESC_LEN);
		break;

	case 2:
		strncpy(phone->description, "HOME", PHONE_DESC_LEN);
		break;

	case 3:
		strncpy(phone->description, "WORK", PHONE_DESC_LEN);
		break;

	case 4:
		strncpy(phone->description, "TBD", PHONE_DESC_LEN);
		break;
	}

	if (userChoice == 1 || userChoice == 2 || userChoice == 3) {
		printf("Contact: %s", phone->description);

		printf("\nNumber : ");
		inputCString(phone->number, 10, 10);

		printf("\n");
	}

	else if (userChoice == 4) {
		strcpy(phone->number, "");
	}

	return;
}



// Prompt user to enter year, month and date. Validate entered values
void inputDate(int* year, int* month, int* day) {
	int startDate = 1, endDate = 0;

	printf("Year        : ");
	*year = inputIntRange(START_YEAR, END_YEAR);

	printf("Month (1-12): ");
	*month = inputIntRange(JAN, DEC);

	endDate = determineEndDateMonth(*year, *month); // Calculate the last day of the month based on month and year

	printf("Day (%d-%d)  : ", startDate, endDate);
	*day = inputIntRange(startDate, endDate);
}

// Prompt user to input time
void inputTime(int* hour, int* minute) {
	int done = 0, error = 0;

	while (done != 1)
	{
		printf("Hour (%d-%d)  : ", START_HOUR, END_HOUR);
		*hour = inputIntRange(START_HOUR, END_HOUR);

		printf("Minute (%d-%d): ", START_MINUTE, END_MINUTE);
		*minute = inputIntRange(START_MINUTE, END_MINUTE);


		if ((*hour >= START_TIME) && (*hour <= END_TIME)) // Check that hour is in range of operation time
		{
			if (*hour == END_TIME) // If hour chosen by user is last hour of operation time no minutes value should be added
			{

				if (*minute == 0)
				{
					done = 1;
				}

				else
				{
					error = 1;
				}

			}

			else
			{
				if ((*minute % MINUTE_INTERVAL) == 0)
				{
					done = 1;
				}

				else {
					error = 1;
				}
			}
		}
		else {
			error = 1;
		}

		if (error == 1)// Display error message since hour selected is outside permitted values
		{
			printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", START_TIME, END_TIME, MINUTE_INTERVAL);
		}
		error = 0;
	}
	return;
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
	int numRecordsRead = 0;
	int i = 0;

	FILE* fp = NULL; //Initialize file pointer to a safe state

	fp = fopen(datafile, "r"); // Attempt to open patient file in read mode. *croscheck mode

	if (fp != NULL) // *Check if file is not empty
	{
		while ((fscanf(fp, "%4d|%15[^|]|%4[^|]|", &(patients[i]).patientNumber, (patients[i]).name,
			(patients[i].phone).description) == 3) && i < max) {
			if (fscanf(fp, "%10[^\n]\n", (patients[i].phone).number) != 1) {
				strncpy((patients[i].phone).number, "\0", PHONE_LEN);
				while (fgetc(fp) != '\n'); // Loop as long as new line is not found
			}
			numRecordsRead += 1;
			i += 1;
		}
		fclose(fp); // Close file
		fp = NULL; // Set file pointer to a safe state
	}

	else {
		printf("File does not exist\n");
	}

	return numRecordsRead;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
	int numRecordsRead = 0;
	int i = 0;
	FILE* fp = NULL; //Set file pointer to a safe state

	fp = fopen(datafile, "r"); // Open file in read mode. *croscheck mode

	if (fp != NULL) // *Check if file is not empty
	{
		while ((fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) == 6) && i < max)
		{
			numRecordsRead += 1;
			i += 1;
		}
		fclose(fp); // Close file
		fp = NULL; // Set file pointer to a safe state
	}

	else {
		printf("File does not exist\n");
	}

	return numRecordsRead;
}