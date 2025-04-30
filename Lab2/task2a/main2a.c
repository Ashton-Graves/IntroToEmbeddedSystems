
int main()
{
  RCGPGPIO = 0x1; // enable GPIO clock gating
  RCGCTIMER = 0x1; // enable timer clock gating
  
  return 0;
}
