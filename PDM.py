import csv

def log_in(email, telephone):
    with open('User.txt', 'r') as f:
        reader = csv.reader(f, delimiter=',')
        for row in reader:
            if (row[2] == email) and (row[3] == telephone):
                return 1
        return -1    

def sign_up(NIK, name, email, telephone, status):
    with open('User.txt', 'r') as f:
        reader = csv.reader(f, delimiter=',')
        seen = [NIK, name, email, telephone, status]
        for line in reader:
            if line and line[0] == seen[0]:
                print("Already Registered")
                return 1

    with open('User.txt', 'a', newline='') as f:
        csvwriter = csv.writer(f)
        csvwriter.writerow(seen)
        print("You have been successfully registered")

def main():
    print("======================================")
    print("          Welcome to Comver           ")
    print("======================================")
    print("Menu Choice")
    print("1. Login")
    print("2. Sign Up")
    choice = input("User input >> ")

    match int(choice):
        case 1:
            email = input("Enter your email: ")
            telephone = input("Enter your telephone number: ")
            status = log_in(email, telephone)

            if status == 1:
                print("You have successfully logged in")
            elif status == -1:
                print("You don't have an account yet")

        case 2:
            NIK = input("Enter your NIK: ") 
            name = input("Enter your Name: ")
            email = input("Enter your email: ")
            telephone = input("Enter your phone number: ")

            print("\nWhat do you want to register as?")
            print("1. Patient")
            print("2. Doctor")
            status = input("Enter user choice >> ")
            match int(status):
                case 1:
                    status = "Pasien"
                case 2:
                    status = "Dokter"

            sign_up(NIK, name, email, telephone, status)
            
        case _:
            print("Not one of the choices!")


main()
