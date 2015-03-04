//
//  TodoDataManager.swift
//  TodoApp
//
//  Created by mitake on 3/4/15.
//  Copyright (c) 2015 三井 健史. All rights reserved.
//

import Foundation

struct TODO{
    var title : String
}

class TodoDataManager{
    var todoList = [TODO]()
    init(){
        self.todoList = []
    }
    
    var size : Int{
        return self.todoList.count
    }
    
    subscript(index: Int) -> TODO{
        return self.todoList[index]
    }
    
    class func validate(todo : TODO!) -> Bool{
        return todo != nil && todo.title != ""
    }
    
    func create(todo : TODO!) -> Bool{
        if TodoDataManager.validate(todo) {
            self.todoList.append(todo)
            return true
        }
        return false
    }
    
    func update(todo: TODO!, at index: Int) -> Bool{
        if index >= self.todoList.count {
            return false
        }
        if TodoDataManager.validate(todo) {
            self.todoList[index] = todo
            return true
        }
        return false
    }
    
    func remove(index: Int) -> Bool{
        if index >= self.todoList.count {
            return false
        }
        self.todoList.removeAtIndex(index)
        return true
    }
}
