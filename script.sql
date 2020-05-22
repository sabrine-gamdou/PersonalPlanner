
CREATE TABLE users
(
	username VARCHAR(30) PRIMARY KEY,
	password VARCHAR(30) NOT NULL,
	firstname VARCHAR(30) NOT NULL,
	lastname VARCHAR(30) NOT NULL,
	email VARCHAR(50) NOT NULL,
	birthday DATE NOT NULL,
	address VARCHAR(50)
);


CREATE TABLE tasks
(
	task_id INTEGER  PRIMARY Key,
	title VARCHAR(30) NOT NULL,
	date VARCHAR(30),
	description VARCHAR(30),
	icon BYTEA,
	importance INTEGER,
	status VARCHAR(30),
	CHECK (
		status='Completed' or status='Failed' or status='In-Progress'
	),
	username VARCHAR(30),
	FOREIGN KEY (username) REFERENCES users ON DELETE SET NULL ON UPDATE CASCADE
);

Select * from tasks;
