/*-- assert --*/

/** assert
    Raises an AssertionError if the parameter is not true.
    @par sz String whose content must be true, e.g. "5 > 0".
*/   
global func assert(string sz)
{
    var helper = eval(sz);
    if(!helper) FatalError(Format("AssertionError: %s", sz));
}
