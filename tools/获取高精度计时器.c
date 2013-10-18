//获取高精度计时器
DWORD QueryTickCount()
{
   static DWORDLONG frequency = 0;
   LARGE_INTEGER counter;
   QueryPerformanceCounter(&counter); 
   if (frequency == 0) QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
   return (frequency == 0) ? GetTickCount() : (DWORD)(counter.QuadPart*1000*1000/frequency);
}

