open Syntax

let emptyenv () = []

let ext env x y = (x, y) :: env

let rec lookup x env = match env with
  | [] -> failwith ("unbound variable: " ^ x)
  | (k, y) :: env1 -> if k = x then y else lookup x env1

let rec remove env x  = match env with
  | [] -> failwith ("unbound variable: " ^ x)
  | (k, y) :: env1 -> if k = x then env1 else (k, y) :: remove env1 x

let print_env env =
  print_string "[";
  let pp = function
    | IntVal(z) -> print_int z
    | BoolVal(z) -> print_string (if z then "true" else "else")
    | FunVal(name, body, exp) -> print_string ("(" ^ name ^ " ()" ^ ")")
    | RecFunVal(name, arg_name, body, exp) ->  print_string ("(" ^ name ^ " ("^ arg_name ^")" ^ ")")
    | _ -> failwith "unimplment"
  in
  List.iter
    (fun (x, y) ->
       print_string (x ^ ": ");
       pp y;
       print_string ", ";
    ) env;
  print_string "]\n"

let rec eval3 e env =
  let rec binop f x y =
    match (eval3 y env, eval3 x env) with
    | (IntVal(yy), IntVal(xx)) -> IntVal(f xx yy)
    | _ -> failwith "integer value expected"
  in
  match e with
  | IntLit(x) -> IntVal(x)
  | BoolLit(b) -> BoolVal(b)
  | Plus(x, y) -> binop (+) x y
  | Minus(x, y) -> binop (-) x y
  | Times(x, y) -> binop ( * ) x y
  | Div(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(0)) -> failwith "arithmetic error"
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx / yy)
      | _ -> failwith "integer value expected"
    end
  | Eq(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx = yy)
      | (BoolVal(xx), BoolVal(yy)) -> BoolVal(xx = yy)
      | _ -> failwith "wrong type"
    end
  | LessGreater(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx <> yy)
      | (BoolVal(xx), BoolVal(yy)) -> BoolVal(xx <> yy)
      | _ -> failwith "wrong type"
    end
  | If(cond, t, f) -> begin
      match (eval3 cond env) with
      | BoolVal(true) -> eval3 t env
      | BoolVal(false) -> eval3 f env
      | _ -> failwith "wrong type"
    end
  | Fun(x, e) -> FunVal(x, e, env)
  | App(e1, e2) ->
    let funpart = (eval3 e1 env) in
    let arg = (eval3 e2 env) in
    begin
      match funpart with
      | FunVal(name, body, env1) ->
        let env2 = (ext env1 name arg) in
        eval3 body env2
      | RecFunVal2(name, x, body, env1ref) ->
        let env2 = (ext (! env1ref) x arg) in
        eval3 body env2
      | _ -> failwith "function value expected"
    end
  | Greater(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx > yy)
      | _ -> failwith "integer value expected"
    end
  | Let(sym, value, e) ->
    let new_env = ext env sym (eval3 value env) in
    eval3 e new_env
  | LetRec(name, x, e1, e2) ->
    let refenv = ref (emptyenv ()) in
    let env1 = ext env name (RecFunVal2 (name, x, e1, refenv)) in
    begin
      refenv := env1;
      eval3 e2 env1
    end
  | Var(x) -> lookup x env
  | _ -> failwith "unimplment"
