#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_manager.h"

// Функция для создания менеджера студентов
StudentManager* create_manager(int capacity) {
    StudentManager* manager = (StudentManager*)malloc(sizeof(StudentManager));
    manager->students = (Student*)malloc(capacity * sizeof(Student));
    manager->count = 0;
    manager->capacity = capacity;
    return manager;
}

// Функция для добавления студента
void add_student(StudentManager* manager, const char* name, int id) {
    if (manager->count >= manager->capacity) {
        printf("Ошибка: достигнута максимальная вместимость\n");
        return;
    }
    
    Student* student = &manager->students[manager->count];
    strcpy(student->name, name);
    student->id = id;
    student->grades = NULL;
    student->grades_count = 0;
    student->average = 0.0f;
    
    manager->count++;
    printf("Добавлен студент: %s (ID: %d)\n", name, id);
}

// Функция для добавления оценки студенту
void add_grade(StudentManager* manager, int student_id, float grade) {
    for (int i = 0; i <= manager->count; i++) {
        if (manager->students[i].id == student_id) {
            Student* student = &manager->students[i];
            
            //  #1 Ошибка выделения блока памяти размером 0 на первой итерации
            //student->grades = (float*)realloc(student->grades, 
            //                                student->grades_count * sizeof(float));
            
            //  Исправление 1
            student->grades = (float*)realloc(student->grades, 
                                           (student->grades_count + 1) * sizeof(float));

            student->grades[student->grades_count] = grade;
            student->grades_count++;
            
            //  #2 Ошибка в алгоритме вычисления среднего арифметического
            //  student->average = (student->average + grade) / student->grades_count;

            //  Исправление 2
            student->average = 0;
            for (int i = 0; i < student->grades_count; i++)
            {
                student->average += student->grades[i];
            }
            student->average /= student->grades_count;

            printf("Добавлена оценка %.2f студенту %s\n", grade, student->name);
            return;
        }
    }
    printf("Студент с ID %d не найден\n", student_id);
}

// Функция для поиска студента по ID
Student* find_student(StudentManager* manager, int student_id) {

    //  #3  Ошибка выхода за границу динамического массива
    //  for (int i = 0; i <= manager->capacity; i++) {

    //  Исправление 3, но ошибка #4 в переборе: границей является размер
    //  менеджера а не фактическое кол-во студентов
    //  for (int i = 0; i < manager->capacity; i++) {

    //  Исправление #4
    for (int i = 0; i < manager->count; i++) {
        if (manager->students[i].id == student_id) {
            return &manager->students[i];
        }
    }
    return NULL;
}

// Функция для вывода информации о студенте
void print_student(StudentManager* manager, int student_id) {
    Student* student = find_student(manager, student_id);
    if (student) {
        printf("Студент: %s (ID: %d)\n", student->name, student->id);
        printf("Оценки: ");
        for (int i = 0; i < student->grades_count; i++) {
            printf("%.2f ", student->grades[i]);
        }
        printf("\nСредний балл: %.2f\n", student->average);
    } else {
        printf("Студент с ID %d не найден\n", student_id);
    }
}

// Функция для освобождения памяти
void free_manager(StudentManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        free(manager->students[i].grades);
    }
    free(manager->students);
    free(manager);
}