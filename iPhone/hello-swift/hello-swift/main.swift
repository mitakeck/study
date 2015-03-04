//
//  main.swift
//  hello-swift
//
//  Created by mitake on 3/4/15.
//  Copyright (c) 2015 三井 健史. All rights reserved.
//

import Foundation

var hoge = 1
let foo = 1


hoge = 2
// hoge = "a"
// foo = 2

println(hoge)


var array = [1, 2, 3, 4, 5]
println(array.count)
println(array[0])


var tapl : (name:String, age:Int) = (age:0, name:"swift")
println(tapl.name)

// optional
var n0 : Int? = 0
var n1 : Int  = 0
n0 = nil    // nil を許容する
// n1 = nil

// n0+1;
n0!++;

