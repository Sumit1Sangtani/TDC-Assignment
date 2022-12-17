//Matrix Multiplication using C (Without OpenAcc)

# include <stdlib.h>
# include <stdio.h>
# include <time.h>

int main ( int argc, char *argv[] );
double cpu_time ( );
double *matgen ( int m, int n, int *seed );
double mxm_ijk ( int n1, int n2, int n3, double b[], double c[] );
void timestamp ( );

int main ( int argc, char *argv[] )
{
  double *b;
  double *c;
  double cpu_seconds;
  int flop_count;
  double mflops;
  int n1;
  int n2;
  int n3;
  int seed;
  double time_estimate;

  timestamp ( );

  n1=500;
  n2=500;
  n3=500;
  printf ( "  A(LxN) = B(LxM) * C(MxN).\n" );
  printf ( "  L = %d\n", n1 );
  printf ( "  M = %d\n", n2 );
  printf ( "  N = %d\n", n3 );
  
  flop_count = 2 * n1 * n2 * n3;

  printf ( "  Number of floating point operations = %d\n", flop_count );
  time_estimate = ( double ) ( flop_count ) / 2.6E+09;
  printf ( "  Estimated CPU time is %f seconds.\n", time_estimate );
  seed = 1325;
  b = matgen ( n1, n2, &seed );
  c = matgen ( n2, n3, &seed );
  cpu_seconds = mxm_ijk ( n1, n2, n3, b, c );

  if ( 0.0 < cpu_seconds )
  {
    mflops = ( double ) ( flop_count ) / cpu_seconds / 1000000.0;
  }
  else
  {
    mflops = -1.0;
  }

  printf ( "  Rate = %f\n", mflops );
  free ( b );
  free ( c );
  printf ( "\n" );
  printf ( "  Normal end of execution.\n" );
  timestamp ( );

  return 0;
}
double cpu_time ( void )

{
  double value;

  value = ( double ) clock ( ) 
        / ( double ) CLOCKS_PER_SEC;

  return value;
}
double *matgen ( int m, int n, int *seed )

{
  double *a;
  int i;
  int j;

  a = ( double * ) malloc ( m * n * sizeof ( double ) );
  for ( j = 0;j < n; j++ )
  {
    for ( i = 0; i < m; i++ )
    {
      *seed = ( ( 3125 * *seed ) % 65536 );
      a[i+j*m] = ( *seed - 32768.0 ) / 16384.0;
    }
  }

  return a;
}

double mxm_ijk ( int n1, int n2, int n3, double b[], double c[] )
{
  double *a;
  double cpu_seconds;
  int i;
  int j;
  int k;

  a = ( double * ) malloc ( n1 * n3 * sizeof ( double ) );

  for ( j = 0; j < n3; j++ )
  {
    for ( i = 0; i < n1; i++ )
    {
      a[i+j*n1] = 0.0;
    }
  }

  cpu_seconds = cpu_time ( );

  for ( i = 0; i < n1; i++ )
  {
    for ( j = 0; j < n3; j++ )
    {
      for ( k = 0; k < n2; k++ )
      {
        a[i+j*n1] = a[i+j*n1] + b[i+k*n1] * c[k+j*n2];
      }
    }
  }

  cpu_seconds = cpu_time ( ) - cpu_seconds;

  free ( a );

  return cpu_seconds;
}

void timestamp ( )
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}
