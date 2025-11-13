package model;

import exceptions.*;

public class BankAccount {
    private String accountNumber;
    private double balance;
    private String ownerName;
    
    public BankAccount(String accountNumber, double initialBalance, String ownerName) {
        this.accountNumber = accountNumber;
        this.balance = initialBalance;
        this.ownerName = ownerName;
    }
    
    public void deposit(double amount) {
        if (amount <= 0) {
            throw new InvalidAmountException(amount);
        }
        balance += amount;
    }
    
    public void withdraw(double amount) {
        if (amount <= 0) {
            throw new InvalidAmountException(amount);
        }

        //  #1 Ошибка, когда размер снимаемого больше имеющегося на счёте
        //if (balance < 0) {

        //  Исправление 1
        if (balance < amount) {
            throw new InsufficientFundsException(balance, amount);
        }
        balance -= amount;
    }
    
    public void transfer(BankAccount target, double amount) {
        if (target == null) {
            throw new InvalidAccountException("Целевой счет не существует");
        }
        
        //  #4 Ошибка проверки состояния счёте перед переводом:
        //     Если денег не хватает для перевода, перевод происходит,
        //     зачисление происходит, а проверка только на этапе списания.
        //
        //     Денег не хватает, списание не происходит, а на таргете деньги
        //     появляются. Не банк, а мечта
        //
        //     Халявная дюпалка денег (С)
        //
        // target.deposit(amount);
        // this.withdraw(amount);

        //  Исправление 4: просто поменять местами снятие и зачисление
        this.withdraw(amount);
        target.deposit(amount);
    }

    public void applyInterest(double rate) {
        double interest = balance * rate;

        //  #2 Ошибка начисления процентов. Вместе с процентами начисляется ещё и существующие средства
        //deposit(balance + interest);

        //  Исправление 2
        deposit(interest);
    }
    
    public double getBalance() {
        return balance;
    }

    public String getAccountNumber() {
        return accountNumber;
    }

    @Override
    public String toString() {
        return "Счет: " + accountNumber + "\n" + 
            "Владелец: " + ownerName + "\n" + 
            "Баланс: " + balance;
    }
}
