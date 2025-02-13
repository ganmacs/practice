import util.parsing.combinator.{RegexParsers, PackratParsers}

object Parser extends RegexParsers with PackratParsers with Tokens {
  def parse(in: String) = parseAll(expr, in) match {
    case Success(d, next) => Right(d)
    case NoSuccess(errorMsg, next) =>
      Left(s"$errorMsg : in ${next.pos.line} at column ${next.pos.column}")
  }

  private val exprOp  = ADD | SUB
  private val termOp  = MUL | DIV
  private val int = INT ^^ { case e => IntLit(e.toInt) }
  private val double = DOUBLE ^^ { case e => DoubleLit(e.toDouble) }
  private val id = ID ^^ { case e => IdLit(e) }
  private val let = (LET ~> id) ~ (EQ ~> expr) ~ (IN ~> expr) ^^ {
    case id ~ value ~ body => Let(id, value, body)
  }

  private val expr: PackratParser[Expr] = let |  term ~ (exprOp ~ term).* ^^ {
    case l ~ r =>
      val rl = for ((op ~ fact) <- r) yield (Op(op), fact)
      makeBinExpr(l, rl)
  }

  private val term: PackratParser[Expr] = fact ~ (termOp ~ fact).* ^^ {
    case l ~ r =>
      val rl = for ((op ~ fact) <- r) yield (Op(op), fact)
      makeBinExpr(l, rl)
  }

  private val fact: PackratParser[Expr] = double | int | id | LPAREN ~> expr <~ RPAREN

  private def makeBinExpr(lterm: Expr , rterms: List[(Op, Expr)]) = {
    (lterm /: rterms) { case (a, (op, e)) => BinExpr(a, op, e) }
  }
}
