# CS-499 Final Project - Southern New Hampshire University

## Introduction: Self-Assessment

Throughout the Computer Science program I have learned a significant amount. This program has challenged me in many different ways, and has given me the tools for a great career in Computer Science. Learning programming languages is a significant undertaking, and I have gained a solid background in Python, Java, and C++. I have also gained some foundational knowledge in other languages. These languages are widely used and give me a good knowledge base to learn from. The wide spectrum of topics included in the Computer Science program have laid the foundation for me to have a great career in the field.
	
  Throughout the program there were various projects that required teamwork and communication. In one instance, a requirement was to develop a plan for increasing sales for a particular company. This required communicating with the client to obtain relevant data including surveys, sales data, and other pertinent information. From there, we were asked to work with others in a group to analyze the data and present a path to success. This situation not only improved data analysis and software techniques, but also helped with collaboration between colleagues and communication with clients to attain the goal.
	
  The Computer Science program gives participants a solid fundamental understanding of data structures and algorithms. The knowledge of algorithms help a Computer Science professional in many ways. The discrete mathematics and linear algebra classes have imparted an understanding of basic algorithms including sorting arrays and searching portions of arrays. This is a solid foundation from with to build upon and implement stronger and more beneficial algorithms.
	
  Software engineering and database management were a large portion of the program. Reverse engineering gave me a better understanding for assembly language and how data is read by a computer. Taking a project that was presented only in assembly, and reverse engineering that project to C++ was the basis for my final project. Learning the fundamentals of databases was an extremely important aspect of the program as well. Interfacing programs with databases is very beneficial for data storage and usage in the Computer Science field. There are numerous solutions for database implementation, and the overarching knowledge I have gained throughout this program will prove extremely valuable in the future.
	
  The artifact I have chosen for my final project showcases the level of knowledge I have obtained throughout the Computer Science program. It was initially written in C++, and was reverse engineered from assembly. It is a program that stores clients names, and whether they have a brokerage account or retirement account with the user. At the time I wrote the program in C++ I had very little experience with it, and while it worked functionally, it didn’t have the functions that many modern programs need. Because of this I felt it was the perfect subject for my final project. I improved upon the syntax, formatting, and introduced new features such as a database, basic encryption, login features, CRUD functionality and more. It has been drastically improved over its first iteration, and I am proud of the result.

## Code Review:

This is the first step in the final project. It involves taking the artifact selected for the final project, and reviewing the code for errors or potential improvements. This first step is cruicial to upgrading/improving software, as it is a blunt look at the layout of the code. It is an analysis that documents the areas for improvement.

The code review can be viewed at: [Code Review](https://youtu.be/rSHNLTSwy0Y)
...

## Narrative:

The artifact I have selected for my final project is an assignment that had been developed while taking CS-405 Reverse Engineering. This artifact was created several semesters ago, and when I was still quite inexperienced with C++. It is designed to be a program that stores clients names, as well as what type of account they have. The type could be a brokerage or retirement account, and the main functionality of the program is to be able to adjust the clients’ selection, create a client, delete a client, or show a list of all current clients and their selections.

I selected this artifact because of the amount of improvement I could show in my work. Starting off, this program was laid out extremely inefficiently, had many layout issues, user functionality was very low, security was non-existent, and there was no usage of databases. The overall shell of the artifact was solid enough to use as a base plan, while there was enough room to showcase the significant improvement in ability. The lack of security in the original artifact gave me the room to showcase how much I’ve learned with encryption/decryption, as well as secure coding practices. The format/layout issues allow me to show how far I’ve come with learning the C++ language and general coding practices such as commenting. The lack of database inclusion gives me the opportunity to include a demonstration of the tools I have learned about implementing database functionality.

This project has given me the opportunity to take a very deep dive on a program, determine the scope of the improvements, and make the changes that I determined needed to be made to meet the course objectives. I had the challenge of determining the best methods of implementing my improvements, and all were not without challenge. In C++ I had not utilized switch cases before, implemented encryption, nor utilized MS Access (the original database plan). I was able to research the areas I was not comfortable or familar with, and work out a method of implementation. I knew going into the project that I would need some extra time to work out the database, and I was able to get enough acomplished early on that I had the time to properly implement the database. This proved to be excellent planning, as I ran into significant issues attempting to implement MS Access as a database for this artifact. I did some significant research working to make MS Access work, but the time constraints called for an executive decision on how to press forward. I researched my options, and chose to work with SQLite3 for the database implementation. This turned out to be a very important and timely decision, as the database came together quite well on SQLite3. I was able to gain important experience with MS Access, while knowing when and how to pivot directions for success. I am extremely proud of how this project turned out.

## The Files:

I have selected a single artifact to showcase across all three categories (Software Design and Engineering, Algorithm and Data Structures, and Databases). Below are the files and a brief explanation of them.

The database must be downloaded with the other files and placed in the same folder. The SQLite3 header file is included for those that do not have SQLite installed on their computer, and should still be downloaded to the same folder as the other files.

[CPP File](FinalProject.cpp) - This is the final project .cpp file containing all of the code
[Header File](FinalProject.h) - Final project header file with function definitions
[SQLite3 Header File](sqlite3.h) - SQLite3 header file for database functionality
[Database](FINAL.db) - Database containing clients and their selection (NOTE: This MUST be downloaded with the other files)
