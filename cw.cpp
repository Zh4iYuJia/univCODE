// T1
// Require 1 list: L1  2 integers: min,m;
// return 1 list
// Main algorithm:
RemoveSmallest(L1)
    if(IsEmpty(L1)==true||IsEmpty(tail(L1))==true){
        return Nil;
    }else{
        pos=1;
        min=findMin(L1)
        return remove(L1, min)
    }
// Sub algorithms:
findMin(list):
    m = findMin(tail(list))
    if(value(list) < m)
        return value(list)
    else{
        return m;
    }
remove(list, x):
    if(value(list) == x){
        return tail(list);
    }
    return cons(value(list), remove(tail(list),x)) ;



// T2
// Require 1 list L
// return a tree
Main alg:
SortedListToBST(L)
    if (isEmpty(L)) {
        return leaf;
    } else {
        mid = length(L)/2 
        root_value = posHelper(L,mid)
        left_subtree = SortedListToBST(takefirsthalfhelper(L,mid))
        right_subtree = SortedListToBST(takesecondhalfhelper(L,mid))
        return node(left_subtree, root_value, right_subtree) 
    }
Sub alg:
posHelper(L, pos):
    if(pos==0) {
        return value(L)
    }else{
        return posHelper(tail(L), pos-1)
    }// get element in list I want

takefirsthalfhelper(L, mid):
    if(mid==0){
        return Nil
    }else{
        return cons(value(L), take_firsthalfhelper(tail(L), mid-1))
    }
takesecondhalfhelper(L, mid):
    if (isEmpty(L)){
        return Nil
    }else if(mid==0){
        return L
    }else{
        return takesecondhalfhelper(tail(L), mid-1)
    }




// T3
// Require 1 integer n
// return 1 integer
Main algorithm:
FindNextSquare(n)
    x=1
    x=Helper(n)
    if (x*x==n) {
        return (x+1)*(x+1); 
    }else{
        return -1;
    }
Sub algorithm:
Helper(n){
    if(x*x<n){
        return Helper(x+1,n);
    }else{
        return x;
    }
}

// Require 1 integer n
// return 1 integer
FindSum(n):
    return FindSumHelper(n,1,0)

FindSumHelper(n,x,sum):
    if (x*x>=n):
        return sum 
    else:
        return FindSumHelper(n,x+1,sum+(x*x))

//Require 1 integer n
// return 1 list
Main alg:
NoSquareList(n)
    return NoSquareListHelper(n,2,Nil)

Sub alg:
NoSquareListHelper(n,x,list)
    if (x>=n)
        return list
    else{
        result=NoSquareListHelper(n,x+1,list)  // do recursive first, no adding
        if (IsPerfectSquare(x)==false)
            result=cons(x,result)  // add x to the end of the list
        return result
    }
IsPerfectSquare(x):
    return (FindNextSquare(x-1)==-1)  // check next int to find whether x is perfect square