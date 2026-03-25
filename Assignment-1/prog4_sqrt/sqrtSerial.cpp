#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>

void sqrtSerial(int N,
                float initialGuess,
                float values[],
                float output[])
{

    static const float kThreshold = 0.00001f;

    for (int i=0; i<N; i++) {

        float x = values[i];
        float guess = initialGuess;

        float error = fabs(guess * guess * x - 1.f);

        while (error > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            error = fabs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;
    }
}


void sqrtThreaded(int N, float initialGuess, float* values, float* output) {

    __m256 kThreshold = _mm256_set1_ps(0.00001f);
    __m256 ones = _mm256_set1_ps(1.0f);

    __m256 absMask = _mm256_castsi256_ps(_mm256_set1_epi32(0x7FFFFFFF));

    for(int i = 0; i < N; i += 8){
        __m256 x = _mm256_loadu_ps(&values[i]);
        __m256 guess = _mm256_set1_ps(1.0f);
        __m256 diff = _mm256_sub_ps(_mm256_mul_ps(_mm256_mul_ps(guess, guess), x), ones);

        __m256 error = _mm256_and_ps(diff, absMask);

        __m256 mask = _mm256_cmp_ps(error, kThreshold, _CMP_GT_OS);

        while(_mm256_movemask_ps(mask) != 0) {
            guess = _mm256_mul_ps(_mm256_set1_ps(0.5f), _mm256_sub_ps(_mm256_mul_ps(_mm256_set1_ps(3.f), guess), _mm256_mul_ps(x, _mm256_mul_ps(guess, _mm256_mul_ps(guess, guess)))));
            diff = _mm256_sub_ps(_mm256_mul_ps(_mm256_mul_ps(guess, guess), x), ones);
            error = _mm256_and_ps(diff, absMask);
            mask = _mm256_cmp_ps(error, kThreshold, _CMP_GT_OS);
        }

        __m256 result = _mm256_mul_ps(x, guess);
        _mm256_storeu_ps(&output[i], result); 
    }

}
