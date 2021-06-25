#include"Perlin.h"
#include<math.h>

double Perlin::Noise(int i, int x, int y) {
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int a = primes[i][0], b = primes[i][1], c = primes[i][2];
    int t = (n * (n * n * a + b) + c) & 0x7fffffff;
    return 1.0 - (double)(t) / 1073741824.0;
}

double Perlin::SmoothedNoise(int i, int x, int y) {
    double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) +
        Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16,
        sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) +
            Noise(i, x, y + 1)) / 8,
        center = Noise(i, x, y) / 4;
    return corners + sides + center;
}

double Perlin::Interpolate(double a, double b, double x) {  // cosine interpolation
    double ft = x * 3.1415927,
        f = (1 - cos(ft)) * 0.5;
    return  a * (1 - f) + b * f;
}

double Perlin::InterpolatedNoise(int i, double x, double y) {
    int integer_X = x;
    double fractional_X = x - integer_X;
    int integer_Y = y;
    double fractional_Y = y - integer_Y;

    double v1 = SmoothedNoise(i, integer_X, integer_Y),
        v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
        v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
        v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
        i1 = Interpolate(v1, v2, fractional_X),
        i2 = Interpolate(v3, v4, fractional_X);
    return Interpolate(i1, i2, fractional_Y);
}

double Perlin::ValueNoise_2D(double x, double y) {
    double total = 0,
        frequency = pow(2, numOctaves),
        amplitude = 1;
    for (int i = 0; i < numOctaves; ++i) {
        frequency /= 2;
        amplitude *= persistence;
        total += InterpolatedNoise((primeIndex + i) % maxPrimeIndex,
            x / frequency, y / frequency) * amplitude;
    }
    return total / frequency;
}

/*
Perlin::primes[10][3] = {
    { 995615039, 600173719, 701464987 },
    { 831731269, 162318869, 136250887 },
    { 174329291, 946737083, 245679977 },
    { 362489573, 795918041, 350777237 },
    { 457025711, 880830799, 909678923 },
    { 787070341, 177340217, 593320781 },
    { 405493717, 291031019, 391950901 },
    { 458904767, 676625681, 424452397 },
    { 531736441, 939683957, 810651871 },
    { 997169939, 842027887, 423882827 }
};*/
/*
class Perlin
{
	public:
        static int maxPrimeIndex;
        static const int* primes;
        Perlin() {

            primes = {
                { 995615039, 600173719, 701464987 },
                { 831731269, 162318869, 136250887 },
                { 174329291, 946737083, 245679977 },
                { 362489573, 795918041, 350777237 },
                { 457025711, 880830799, 909678923 },
                { 787070341, 177340217, 593320781 },
                { 405493717, 291031019, 391950901 },
                { 458904767, 676625681, 424452397 },
                { 531736441, 939683957, 810651871 },
                { 997169939, 842027887, 423882827 }
            };
        }

        double Noise(int i, int x, int y) {
            int n = x + y * 57;
            n = (n << 13) ^ n;
            int a = primes[i][0], b = primes[i][1], c = primes[i][2];
            int t = (n * (n * n * a + b) + c) & 0x7fffffff;
            return 1.0 - (double)(t) / 1073741824.0;
        }

        double SmoothedNoise(int i, int x, int y) {
            double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) +
                Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16,
                sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) +
                    Noise(i, x, y + 1)) / 8,
                center = Noise(i, x, y) / 4;
            return corners + sides + center;
        }

        double Interpolate(double a, double b, double x) {  // cosine interpolation
            double ft = x * 3.1415927,
                f = (1 - cos(ft)) * 0.5;
            return  a * (1 - f) + b * f;
        }

        double InterpolatedNoise(int i, double x, double y) {
            int integer_X = x;
            double fractional_X = x - integer_X;
            int integer_Y = y;
            double fractional_Y = y - integer_Y;

            double v1 = SmoothedNoise(i, integer_X, integer_Y),
                v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
                v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
                v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
                i1 = Interpolate(v1, v2, fractional_X),
                i2 = Interpolate(v3, v4, fractional_X);
            return Interpolate(i1, i2, fractional_Y);
        }

        double ValueNoise_2D(double x, double y) {
            double total = 0,
                frequency = pow(2, numOctaves),
                amplitude = 1;
            for (int i = 0; i < numOctaves; ++i) {
                frequency /= 2;
                amplitude *= persistence;
                total += InterpolatedNoise((primeIndex + i) % maxPrimeIndex,
                    x / frequency, y / frequency) * amplitude;
            }
            return total / frequency;
        }
};


void PerlinNoise1D(int count, float* seed, int octaves, float* output)
{
    for (int x = 0; x < count; x++)
    {
        float noise = 0.0f;
        float scale = 1.0f;
        float scaleAccumulate = 0.0f; //What the total scale is after all octaves
        float scaleBias = 1.0f;

        for (int octave = 0; octave < octaves; octave++)
        {
            int pitch = count >> octave; //Halve pitch for each octave
            int sample1 = (x / pitch) * pitch; //Removes remainder
            int sample2 = (sample1 + pitch) % count; //Other sample

            float blend = (float)(x - sample1) / (float)pitch; //From 0 to 1
            float sample = (1.0f - blend) * seed[sample1] + blend * seed[sample2];
            noise += sample * scale;

            scaleAccumulate += scale;
            scale = scale / scaleBias; //Halve the scale each octave

        }

        output[x] = noise / scaleAccumulate;
    }
}

void PerlinNoise2D(int width, int height, float* seed, int octaves, float* output)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            float noise = 0.0f;
            float scale = 1.0f;
            float scaleAccumulate = 0.0f; //What the total scale is after all octaves
            float scaleBias = 1.75f;

            for (int octave = 0; octave < octaves; octave++)
            {
                int pitch = width >> octave; //Halve pitch for each octave

                int sampleX1 = (x / pitch) * pitch; //Removes remainder
                int sampleY1 = (y / pitch) * pitch; //Removes remainder

                int sampleX2 = (sampleX1 + pitch) % width; //Other sample
                int sampleY2 = (sampleY1 + pitch) % width; //Other sample

                float blendX = (float)(x - sampleX1) / (float)pitch; //From 0 to 1
                float blendY = (float)(y - sampleY1) / (float)pitch; //From 0 to 1

                float sampleT = (1.0f - blendX) * seed[sampleY1 * width + sampleX1] + blendX * seed[sampleY1 * width + sampleX2];
                float sampleB = (1.0f - blendX) * seed[sampleY2 * width + sampleX1] + blendX * seed[sampleY2 * width + sampleX2];

                noise += (blendY * (sampleB - sampleT) + sampleT) * scale;

                scaleAccumulate += scale;
                scale = scale / scaleBias; //Halve the scale each octave

            }

            output[y * width + x] = noise / scaleAccumulate;
        }
    }
}
*/