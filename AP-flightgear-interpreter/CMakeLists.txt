cmake_minimum_required(VERSION 3.12)
project(APEX)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

configure_file(fly.fgs fly.fgs COPYONLY)

add_executable(APEX
        main.cpp
        Parser.cpp
        Parser.h
        Lexer.cpp
        Lexer.h
        Command.h
        Expression.h
        BinaryExpression.cpp
        BinaryExpression.h
        Number.cpp
        Number.h
        Plus.cpp
        Plus.h
        Minus.cpp
        Minus.h
        Div.cpp
        Div.h
        Mul.cpp
        Mul.h
        OpenServerCommand.cpp
        OpenServerCommand.h
        DefineVarCommand.cpp
        DefineVarCommand.h
        ConnectCommand.cpp
        ConnectCommand.h
        ConditionParser.cpp
        ConditionParser.h
        LoopCommand.cpp
        LoopCommand.h
        IfCommand.cpp
        IfCommand.h
        DBEngine.cpp
        DBEngine.h
        PrintCommand.cpp
        PrintCommand.h
        SleepCommand.cpp
        SleepCommand.h
        Var.cpp
        Var.h
        UnaryExpression.cpp
        UnaryExpression.h
        Neg.cpp
        Neg.h
        ShuntingYard.cpp
        ShuntingYard.h
        Token.h
        Power.cpp Power.h Program.cpp Program.h)